package com.example.myleaveprocesser.controller;



import com.example.myleaveprocesser.model.LeaveModel;
import com.example.myleaveprocesser.model.LeaveType;
import com.example.myleaveprocesser.repository.LeaveRepository;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class LeaveProcessorController {

    private final LeaveRepository leaveRepository;

    public LeaveProcessorController(LeaveRepository leaveRepository) {
        this.leaveRepository = leaveRepository;
    }

    @GetMapping("/")
    public String home(Model model) {
        model.addAttribute("leaveRequests", leaveRepository.findAll());
        model.addAttribute("leaveRequest", new LeaveModel());
        model.addAttribute("leaveTypes", LeaveType.values());
        model.addAttribute("days", leaveRepository.findTotalDaysOfAllLeaves());


        return "index";
    }

    @PostMapping("/leaveRequest")
    public String leaveRequest(@ModelAttribute LeaveModel leaveModel, Model model) {

        if (leaveModel.getEndDate().isBefore(leaveModel.getStartDate())) {
            model.addAttribute("error", "End date is before start date");
            model.addAttribute("leaveRequests", leaveRepository.findAll());
            model.addAttribute("leaveRequest", leaveModel);
            model.addAttribute("leaveTypes", LeaveType.values());
            model.addAttribute("days", leaveRepository.findTotalDaysOfAllLeaves());

            return "index";
        }
        if(leaveRepository.existsOverlappingBooking(leaveModel.getEmployeeName(),leaveModel.getStartDate(),leaveModel.getEndDate())) {
            model.addAttribute("error", "Leave already exists");
            model.addAttribute("leaveRequests", leaveRepository.findAll());
            model.addAttribute("leaveRequest", leaveModel);
            model.addAttribute("leaveTypes", LeaveType.values());
            model.addAttribute("days", leaveRepository.findTotalDaysOfAllLeaves());

            return "index";
        }
        leaveRepository.save(leaveModel);
        return "redirect:/";
    }

    @GetMapping("/edit/{id}")
    public String editLeaveRequest(@PathVariable Long id, Model model) {
        LeaveModel leaveModel = leaveRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Leave not found with id: " + id));
        model.addAttribute("leaveRequest", leaveModel);
        model.addAttribute("leaveTypes", LeaveType.values());
        model.addAttribute("days", leaveRepository.findTotalDaysOfAllLeaves());
        model.addAttribute("leaveRequests", leaveRepository.findAll());
        return "index";
    }

    @PostMapping("/update/{id}")
    public String updateLeaveRequest(@PathVariable Long id, LeaveModel leaveModel) {
        LeaveModel existingLeaveModel = leaveRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Leave not found with id: " + id));


        existingLeaveModel.setEndDate(leaveModel.getEndDate());
        existingLeaveModel.setStartDate(leaveModel.getStartDate());
        leaveRepository.save(existingLeaveModel);
        return "redirect:/";
    }

    @PostMapping("/delete/{id}")
    public String deleteLeaveRequest(@PathVariable Long id, Model model) {
        leaveRepository.deleteById(id);
        return "redirect:/";
    }
}

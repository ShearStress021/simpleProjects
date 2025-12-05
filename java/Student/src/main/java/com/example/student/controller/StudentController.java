package com.example.student.controller;

import com.example.student.model.Student;
import com.example.student.service.StudentService;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;


@Controller
@RequestMapping
@RequiredArgsConstructor
public class StudentController {
    private final StudentService service;

    @GetMapping("/")
    public String home() {return "redirect:/students";}



    @GetMapping({"/students", "/index"})
    public String list(
            @RequestParam(name = "keyword", required = false) String
                    keyword,
            @RequestParam(defaultValue = "0") int page,
            @RequestParam(defaultValue = "10") int size,
            Model model
    ) {
        var pageStudents = service.search(keyword, page, size);
        model.addAttribute("pageStudents", pageStudents);
        model.addAttribute("students", pageStudents.getContent());
        model.addAttribute("keyword", keyword == null ? "" : keyword);
        model.addAttribute("currentPage", page);
        model.addAttribute("pageSize", size);
        return "students";
    }
    // Show create form
    @GetMapping("/students/new")
    public String createForm(Model model) {
        model.addAttribute("student", new Student());
        return "student-form";
    }
    // Persist (create)
    @PostMapping("/students")
    public String create(@Valid @ModelAttribute("student") Student student,
                         BindingResult br,
                         RedirectAttributes ra) {
        if (br.hasErrors()) return "student-form";
        service.save(student);
        ra.addFlashAttribute("success", "Student created successfully.");
        return "redirect:/students";
    }
    // Show edit form
    @GetMapping("/students/{id}/edit")
    public String editForm(@PathVariable Long id, Model model) {
        model.addAttribute("student", service.get(id));
        return "student-form";
    }
    @PostMapping("/students/{id}")
    public String update(@PathVariable Long id,
                         @Valid @ModelAttribute("student") Student student,
                         BindingResult br,
                         RedirectAttributes ra) {
        if (br.hasErrors()) return "student-form";
        student.setId(id);
        service.save(student);
        ra.addFlashAttribute("info", "Student updated successfully.");
        return "redirect:/students";
    }
    // Delete via POST (safer than GET)
    @PostMapping("/students/{id}/delete")
    public String delete(@PathVariable Long id, RedirectAttributes ra) {
        service.delete(id);
        ra.addFlashAttribute("warning", "Student deleted.");
        return "redirect:/students";
    }

}

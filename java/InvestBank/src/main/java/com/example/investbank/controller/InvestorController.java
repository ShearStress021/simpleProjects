package com.example.investbank.controller;


import com.example.investbank.model.Investor;
import com.example.investbank.model.Projection;
import com.example.investbank.model.SaveType;
import com.example.investbank.service.InvestorService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import java.util.List;

@Controller
@RequiredArgsConstructor
@RequestMapping("/")
public class InvestorController {
    private final InvestorService service;

    @GetMapping("/")
    public String show() {
        return "redirect:/home";
    }

    @GetMapping("/home")
    public String home( Model model) {
      List<Investor> investors = service.findAllInvestors();
      double total = service.calculateTotalInitialDeposit();
      double regular = service.calculateTotalDepositBySaveTypeRegular();
      double deluxe = service.calculateTotalDepositBySaveTypeDeluxer();
      model.addAttribute("investors",investors);
      model.addAttribute("total",total);
      model.addAttribute("regular",regular);
      model.addAttribute("deluxe",deluxe);
      return "home";
    }

    @GetMapping("/add")
    public String showInvestorForm(Model model) {
        model.addAttribute("investor", new Investor());
        model.addAttribute("types", SaveType.values());
        return "form-investor";
    }

    @PostMapping("/add")
    public String addInvestor(@ModelAttribute("investor") Investor investor, RedirectAttributes ra ) {
        if (service.investorExistsByCode(investor.getCode())) {
            ra.addFlashAttribute("errorMessage", "Investor already exists");
            return "redirect:/add";
        }
        service.saveInvestor(investor);
        ra.addFlashAttribute("successMessage", "Investor has been added");
        return "redirect:/home";

    }


    @GetMapping("/projections/{id}")
    public String showInvestorProjection(@PathVariable Long id, Model model) {

        Investor investor = service.findInvestorById(id);
        List<Projection> projections = service.getInvestorProjections(investor);


        model.addAttribute("investor",investor);
        model.addAttribute("projections",projections);
        return "projections";
    }


    @GetMapping("/edit/{id}")
    public String editShowInvestor(@PathVariable Long id, Model model) {
        Investor investor = service.findInvestorById(id);
        model.addAttribute("investor", investor);
        model.addAttribute("types", SaveType.values());
        return "form-investor";

    }

    @PostMapping("/edit/{id}")
    public String editInvestor(@ModelAttribute("investor")  Investor investor,
                               @PathVariable Long id,
                               RedirectAttributes ra ) {

        Investor existingInvestor = service.findInvestorById(id);
        if (existingInvestor == null) {
            ra.addFlashAttribute("errorMessage", "Investor already  does not exists");
            return "redirect:/add";
        }
        existingInvestor.setCode(investor.getCode());
        existingInvestor.setName(investor.getName());
        existingInvestor.setInitialDeposit(investor.getInitialDeposit());
        existingInvestor.setYears(investor.getYears());
        existingInvestor.setSaveType(investor.getSaveType());
        service.updateInvestorInfo(existingInvestor);

        ra.addAttribute("successMessage", "Investor has been updated");
        return "redirect:/home";
    }

    @PostMapping("/{id}/delete")
    public String deleteInvestor(@PathVariable Long id, RedirectAttributes ra ) {
        Investor investor = service.findInvestorById(id);
        if (investor == null) {
            ra.addFlashAttribute("errorMessage", "Investor already  does not exists");
            return "redirect:/home";
        }
        service.deleteInvestor(investor);
        return  "redirect:/home";
    }











}

package com.example.investbank.controller;

import com.example.investbank.model.Investor;
import com.example.investbank.repository.InvestorRepository;
import com.example.investbank.service.InvestorService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.ui.Model;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

class InvestorControllerTest {

    @Mock
    private InvestorRepository repo;

    @Mock
    private InvestorService service;


    @Mock
    private Model model;

    @Mock
    private RedirectAttributes ra;

    @InjectMocks
    private InvestorController controller;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.initMocks(this);
    }

    @Test
    void testListInvestors() {
        List<Investor> investors = List.of(new Investor());

        when(service.findAllInvestors()).thenReturn(investors);

        String view = controller.home(model);
        verify(model).addAttribute("investors",investors);
        assertEquals("home", view);
    }

    @Test
    void testAddInvestorAlreadyExists() {
        Long id = 1L;
        Investor investor = new Investor();
        investor.setId(id);
        investor.setCode("122");
        when(service.investorExistsByCode("122")).thenReturn(true);

        String view = controller.addInvestor(investor, ra);
        verify(ra).addFlashAttribute("errorMessage","Investor already exists");
        assertEquals("redirect:/add", view);
        verify(service,never()).saveInvestor(any());
    }

    @Test
    void testAddNewInvestor() {
        Long id = 1L;
        Investor investor = new Investor();
        investor.setId(id);
        investor.setCode("133");
        when(service.investorExistsByCode("133")).thenReturn(false);
        String view = controller.addInvestor(investor, ra);
        verify(service).saveInvestor(investor);
        verify(ra).addFlashAttribute("successMessage","Investor has been added");
        assertEquals("redirect:/home", view);
    }
}
package com.example.investbank.controller;

import com.example.investbank.model.Investor;
import com.example.investbank.model.SaveType;
import com.example.investbank.service.InvestorService;
import jakarta.persistence.*;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.ArgumentCaptor;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.webmvc.test.autoconfigure.AutoConfigureMockMvc;
import org.springframework.boot.webmvc.test.autoconfigure.WebMvcTest;
import org.springframework.test.util.ReflectionTestUtils;
import org.springframework.test.web.servlet.MockMvc;


import static org.assertj.core.api.AssertionsForClassTypes.assertThat;
import static org.mockito.Mockito.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

@SpringBootTest
@AutoConfigureMockMvc
class InvestorControllerMockTest {

    @Autowired
    private MockMvc mockMvc;

    @Autowired
    private InvestorController controller;

    @Autowired
    private InvestorService mockService;

    @BeforeEach
    void setUp() {
        mockService = Mockito.mock(InvestorService.class);
        ReflectionTestUtils.setField(controller, "service", mockService);

    }
    @Test
    void testHomeRedirectToHome()  throws Exception {
        mockMvc.perform(get("/"))
                .andExpect(status().is3xxRedirection())
                .andExpect(redirectedUrl("/home"));
    }
    @Test
    void testListInvestorDisplay()  throws Exception {
        List<Investor> fakeList = List.of(new Investor());
        when(mockService.findAllInvestors()).thenReturn(fakeList);

        mockMvc.perform(get("/home"))
                .andExpect(status().isOk())
                .andExpect(view().name("home"))
                .andExpect(model().attributeExists("investors"))
                .andExpect(model().attribute("investors", fakeList));

    }
    @Test
    void testAddInvestorForm()  throws Exception {
        mockMvc.perform(get("/add"))
                .andExpect(status().isOk())
                .andExpect(view().name("form-investor"))
                .andExpect(model().attributeExists("investor"));

    }

    @Test
    void testAddInvestor()  throws Exception {


        mockMvc.perform(post("/add")
                    .param("code", "12323")
                    .param("name", "test")
                    .param("initialDeposit", "10000")
                    .param("year", "4")
                    .param("saveType", "REGULAR"))
                .andExpect(status().is3xxRedirection())
                .andExpect(redirectedUrl("/home"));
    }

    @Test
    void testUpdateInvestor()  throws Exception {

        Long id = 1L;
        Investor existinginvestor = new Investor();
        existinginvestor.setId(id);
        existinginvestor.setName("test");
        existinginvestor.setCode("12323");

        when(mockService.findInvestorById(id)).thenReturn(existinginvestor);

        mockMvc.perform(post("/edit/" + id)
                        .param("code", "12323")
                        .param("name", "test")
                        .param("initialDeposit", "10000")
                        .param("year", "4")
                        .param("saveType", "REGULAR"))
                .andExpect(status().is3xxRedirection());
//                .andExpect(redirectedUrl("/home?successMessage=Investor+has+been+updated"));
        ArgumentCaptor<Investor> captor = ArgumentCaptor.forClass(Investor.class);
        verify(mockService).updateInvestorInfo(captor.capture());
        Investor updated = captor.getValue();

        assertThat(updated.getId()).isEqualTo(1L);
        assertThat(updated.getName()).isEqualTo("test");
        assertThat(updated.getCode()).isEqualTo("12323");

        verify(mockService, times(1)).findInvestorById(id);
    }

    @Test
    void testDeleteInvestor()  throws Exception {
        Long id = 1L;
        Investor existinginvestor = new Investor();
        existinginvestor.setId(id);

        when(mockService.findInvestorById(id)).thenReturn(existinginvestor);
        mockMvc.perform(post("/"+ id + "/delete"))
                .andExpect(status().is3xxRedirection())
                .andExpect(redirectedUrl("/home"));
        verify(mockService).findInvestorById(id);
        verify(mockService, times(1)).deleteInvestor(existinginvestor);
    }







}
package com.example.leaverequest.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class LeaveRequestController {

    @GetMapping("/")
    public String index() {
        return "index";
    }
}

package com.example.leaveprocessor;

import lombok.AllArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
@AllArgsConstructor
public class LeaveControler {

    @GetMapping("/")
    public String home() {
        return "home";
    }
}

package com.example.inventorysystem.controller;

import com.example.inventorysystem.repository.CategoryRepository;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

public class CategoryController {

    private final CategoryRepository categoryRepo;

    public CategoryController(CategoryRepository categoryRepo) {
        this.categoryRepo = categoryRepo;
    }

    @GetMapping("/")
    public String list(Model model){
        return "catogory";
    }
}

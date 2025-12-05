package com.example.student.controller;

import com.example.student.model.Student;
import com.example.student.repository.StudentRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

class StudentControllerTest {
    @Mock
    private StudentRepository repo;

    @Mock
    private Model model;

    @Mock
    private RedirectAttributes ra;

    @Mock
    private BindingResult br;

    @InjectMocks
    private StudentController controller;


    @BeforeEach
    void setUp() {
        MockitoAnnotations.openMocks(this);
    }
//
//    @Test
//    void testListShouldAddStudent() {
//        List<Student> students = List.of(new Student());
//
//        when(repo.findAll()).thenReturn(students);
//        String view = controller.list()
//    }

    @Test
    void testAddWhenCategoryAlreadyExists() {
        Long id = 1L;
        Student student = new Student();
        when(repo.existsById(id)).thenReturn(true);
        String view = controller.create(student, br, ra);
        verify(ra).addFlashAttribute("error", "Category already exists");
//        assertEquals("redirect:/students", view);
        verify(repo, never()).save(any());
    }


    @Test
    void home() {
    }

    @Test
    void list() {
    }

    @Test
    void createForm() {
    }

    @Test
    void create() {
    }

    @Test
    void editForm() {
    }

    @Test
    void update() {
    }

    @Test
    void delete() {
    }
}
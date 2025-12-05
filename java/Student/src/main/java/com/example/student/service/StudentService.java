package com.example.student.service;



import com.example.student.model.Student;
import com.example.student.repository.StudentRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.data.domain.*;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;


@Service
@RequiredArgsConstructor
public class StudentService {
    private final StudentRepository repo;
    public Page<Student> search(String keyword, int page, int size) {
        Pageable pageable = PageRequest.of(page, size,
                Sort.by("id").ascending());
        if (keyword == null || keyword.isBlank()) {
            return repo.findAll(pageable);
        }
        // If keyword is numeric, try ID match first
        try {
            Long id = Long.parseLong(keyword.trim());
            Optional<Student> one = repo.findById(id);
            return one.map(s -> new PageImpl<>(List.of(s), pageable, 1))
                    .orElseGet(() -> new PageImpl<>(List.of(), pageable,
                            0));
        } catch (NumberFormatException ignore) {
            return repo.findByNameContainingIgnoreCase(keyword.trim(),
                    pageable);
        }
    }
    public Student get(Long id) { return repo.findById(id).orElseThrow(); }
    public Student save(Student s) { return repo.save(s); }
    public void delete(Long id) { repo.deleteById(id); }
}


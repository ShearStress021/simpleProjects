package com.example.investbank.model;

import jakarta.persistence.*;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import lombok.Data;


@Entity
@Data
public class Investor {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @NotNull
    @Column(nullable = false, unique = true)
    private String code;

    @NotBlank
    private String name;

    @Min(0)
    private double initialDeposit;

    @Min(1)
    private int years;

    @Enumerated(EnumType.STRING)
    private SaveType saveType;
}

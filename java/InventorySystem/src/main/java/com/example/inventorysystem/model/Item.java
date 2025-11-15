package com.example.inventorysystem.model;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

@Entity
@Table(name = "items")
@Getter
@Setter
public class Item {
    @Id
    private String itemcode;

    private String itemdesc;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "catcode", nullable = false)
    private Category category;

}

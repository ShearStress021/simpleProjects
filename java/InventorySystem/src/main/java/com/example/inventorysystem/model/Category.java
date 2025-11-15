package com.example.inventorysystem.model;


import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;
import org.hibernate.cache.spi.support.AbstractReadWriteAccess;

import java.util.List;

@Entity
@Table(name = "category")
@Getter
@Setter
public class Category {
    @Id
    private String catcode;

    private String catdesc;


    @OneToMany(mappedBy = "category", fetch = FetchType.LAZY, cascade = CascadeType.ALL)
    private List<Item> items;
}

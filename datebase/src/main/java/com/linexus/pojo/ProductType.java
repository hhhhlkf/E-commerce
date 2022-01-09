package com.linexus.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.jws.WebService;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 9:11
 */
@WebService
@NoArgsConstructor
@AllArgsConstructor
@Data
public class ProductType {
    String typeName;
    int typeId;
    String typeProduct;
    int typeProductId;
}

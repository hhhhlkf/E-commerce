package com.linexus.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.jws.WebService;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 9:09
 */
@WebService
@Data
@AllArgsConstructor
@NoArgsConstructor
public class Product {
    int productId;
    String productName;
    int productPrice;
    int productNum;
    int productBuyNum;
    String productImage;
    float productDiscount;
}

package com.linexus.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

import javax.jws.WebService;
import java.math.BigDecimal;
import java.sql.Timestamp;
import java.util.Date;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 9:11
 */
@WebService
@AllArgsConstructor
@NoArgsConstructor
@Data
public class Order {
    int orderId;
    String orderProductName;
    int orderProductNum;
    String orderProductStyle;
    int orderProductId;
    BigDecimal orderCost;
    Date orderTime;
    String orderClient;
    int orderClientId;
    int orderCheck;
    int orderHide;

}

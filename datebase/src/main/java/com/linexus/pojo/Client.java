package com.linexus.pojo;

import lombok.*;

import javax.jws.WebService;
import java.sql.Timestamp;
import java.util.Date;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 9:08
 */
@WebService
@AllArgsConstructor
@NoArgsConstructor
@Data
@ToString
public class Client {

    String clientName;
    int clientId;
    String clientPhone;
    String clientEmail;
    Date clientSignTime;
    String clientPwd;
    int clientBought;
    String clientImage;
}

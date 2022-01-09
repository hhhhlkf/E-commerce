package com.linexus.dao;

import com.linexus.pojo.Client;
import org.apache.ibatis.annotations.Param;

import javax.jws.WebMethod;
import javax.jws.WebService;
import java.util.List;
import java.util.Map;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 9:13
 */
@WebService
public interface ClientMapper {
    @WebMethod
    public List<Client> getClientList();
    @WebMethod
    public Client getClientByNameAndPwd(@Param("name") String name,@Param("pwd") String pwd);
    @WebMethod
    public void InsertClient(Client client);
    @WebMethod
    public void deleteClientByNameAndPwd(@Param("name") String name,@Param("pwd") String pwd);
    @WebMethod
    public void updateClient(Client client);
    @WebMethod
    List<Client> getClientLikeList(@Param("mess") String mess);
}

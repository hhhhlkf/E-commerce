package com.linexus.service;

import com.linexus.dao.ClientMapper;
import com.linexus.pojo.Client;
import org.mybatis.spring.support.SqlSessionDaoSupport;

import javax.jws.WebService;
import java.util.List;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 10:28
 */
@WebService(serviceName = "ClientMapper")
public class ClientMapperImpl extends SqlSessionDaoSupport implements ClientMapper {
    @Override
    public List<Client> getClientList() {
        return getSqlSession().getMapper(ClientMapper.class).getClientList();
    }

    @Override
    public Client getClientByNameAndPwd(String name, String pwd) {
        return getSqlSession().getMapper(ClientMapper.class).getClientByNameAndPwd(name,pwd);
    }

    @Override
    public void InsertClient(Client client) {
        getSqlSession().getMapper(ClientMapper.class).InsertClient(client);
    }

    @Override
    public void deleteClientByNameAndPwd(String name, String pwd) {
        getSqlSession().getMapper(ClientMapper.class).deleteClientByNameAndPwd(name,pwd);
    }

    @Override
    public void updateClient(Client client) {
        getSqlSession().getMapper(ClientMapper.class).updateClient(client);
    }

    @Override
    public List<Client> getClientLikeList(String mess) {
        return getSqlSession().getMapper(ClientMapper.class).getClientLikeList(mess);
    }
}

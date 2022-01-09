package com.linexus.service;

import com.linexus.dao.ProductMapper;
import com.linexus.dao.ProductTypeMapper;
import com.linexus.pojo.ProductType;
import org.mybatis.spring.support.SqlSessionDaoSupport;

import javax.jws.WebService;
import java.util.List;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 10:29
 */
@WebService(serviceName = "ProductTypeMapper")
public class ProductTypeMapperImpl extends SqlSessionDaoSupport implements ProductTypeMapper {

    @Override
    public List<ProductType> getProductTypeByProName(String name) {
        return getSqlSession().getMapper(ProductTypeMapper.class).getProductTypeByProName(name);
    }

    @Override
    public void addProductType(ProductType type) {
        getSqlSession().getMapper(ProductTypeMapper.class).addProductType(type);
    }

    @Override
    public void deleteProductTypeByName(String name) {
        getSqlSession().getMapper(ProductTypeMapper.class).deleteProductTypeByName(name);
    }
}

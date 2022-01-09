/*
 Navicat Premium Data Transfer

 Source Server         : SQLnet
 Source Server Type    : MySQL
 Source Server Version : 50717
 Source Host           : localhost:3306
 Source Schema         : cppdatabase

 Target Server Type    : MySQL
 Target Server Version : 50717
 File Encoding         : 65001

 Date: 09/01/2022 16:00:24
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for client
-- ----------------------------
DROP TABLE IF EXISTS `client`;
CREATE TABLE `client`  (
  `client_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '用户名',
  `client_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '用户编号',
  `client_phone` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '用户名',
  `client_email` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '用户邮箱',
  `client_sign_time` date NULL DEFAULT NULL COMMENT '用户创建时间',
  `client_pwd` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '用户密码',
  `client_bought` int(11) NULL DEFAULT NULL COMMENT '用户购买数',
  `client_image` varchar(500) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '用户头像',
  PRIMARY KEY (`client_id`) USING BTREE,
  INDEX `client_name`(`client_name`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 23 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of client
-- ----------------------------
INSERT INTO `client` VALUES ('lkf', 1, '13663890201', 'likefan@gmail.com', '2021-12-15', '12378945a', 6861, 'D:/code/Qt/C++project/imagebase/nzk.jpg');
INSERT INTO `client` VALUES ('栾帅', 2, '18137974607', 'luanshuai@jlu.cn', '2021-12-16', '1234567890', 6000, 'D:/code/Qt/C++project/imagebase/头像男孩.svg');
INSERT INTO `client` VALUES ('吴国梁', 3, '1231252534265', 'wgliang@jlu.cn', '2021-12-20', '1235377434', 1384, 'D:/code/Qt/C++project/imagebase/头像男孩.svg');
INSERT INTO `client` VALUES ('王海鹏', 4, '13353902646', 'whpeng', '2021-12-15', '123456', 1000, 'D:/code/Qt/C++project/imagebase/头像男孩.svg');
INSERT INTO `client` VALUES ('你好', 8, '', '', '2021-10-13', '123456789', 1010, '');
INSERT INTO `client` VALUES ('你爸爸', 14, '321654734589', NULL, NULL, '12345678901', 400, NULL);
INSERT INTO `client` VALUES ('1111', 17, '1111', '1111', '2021-12-24', '1111', 0, '');
INSERT INTO `client` VALUES ('12312312', 18, '12313123213', '1232131', '2021-12-24', '123123131', 0, '');
INSERT INTO `client` VALUES ('老师', 19, '13353902646', 'jlu@edu.cn', '2021-12-31', '12378945a', 0, 'D:/code/Qt/C++project/imagebase/freedom-gundam2.0.jpg');
INSERT INTO `client` VALUES ('你好', 21, '12345678900', '@jlu.edu.cnn', '2022-01-01', '12378945a', 0, 'D:/code/Qt/C++project/imagebase/mobile5.jpeg');
INSERT INTO `client` VALUES ('你好啊', 22, '1234567890', '@jlu.edu.cn', '2022-01-01', '12378945a', -2000, '');

-- ----------------------------
-- Table structure for order
-- ----------------------------
DROP TABLE IF EXISTS `order`;
CREATE TABLE `order`  (
  `order_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '订单编号',
  `order_product_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '订单名称',
  `order_product_num` int(11) NOT NULL COMMENT '订单个数',
  `order_product_style` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '订单物品种类',
  `order_product_id` int(11) NULL DEFAULT NULL COMMENT '订单物品的编号',
  `order_cost` decimal(65, 2) NOT NULL COMMENT '订单花费金额',
  `order_time` date NULL DEFAULT NULL COMMENT '订单的消费时间',
  `order_client` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '订单的消费人',
  `order_client_id` int(11) NULL DEFAULT NULL COMMENT '订单消费人的编号',
  `order_check` int(11) NOT NULL COMMENT '订单的为购物车还是消费记录',
  `order_hide` int(11) NOT NULL COMMENT '订单是否被隐藏',
  PRIMARY KEY (`order_id`) USING BTREE,
  INDEX `order_client`(`order_client`) USING BTREE,
  INDEX `order_client_id`(`order_client_id`) USING BTREE,
  INDEX `order_product_id`(`order_product_id`) USING BTREE,
  INDEX `order_ibfk_4`(`order_product_name`) USING BTREE,
  CONSTRAINT `order_ibfk_1` FOREIGN KEY (`order_client`) REFERENCES `client` (`client_name`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `order_ibfk_2` FOREIGN KEY (`order_client_id`) REFERENCES `client` (`client_id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `order_ibfk_3` FOREIGN KEY (`order_product_id`) REFERENCES `product` (`product_id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `order_ibfk_4` FOREIGN KEY (`order_product_name`) REFERENCES `product` (`product_name`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 78 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of order
-- ----------------------------
INSERT INTO `order` VALUES (1, '柯西高达', 3, 'normal', 1, 100.00, '2021-12-15', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (2, '自由高达', 2, 'normal', 2, 200.00, '2021-12-15', '吴国梁', 3, -1, -1);
INSERT INTO `order` VALUES (3, '元祖高达', 1, 'normal', 3, 100.00, '2021-12-15', '栾帅', 2, 1, -1);
INSERT INTO `order` VALUES (4, '白高达', 4, 'normal', 13, 500.00, '2021-12-10', '王海鹏', 4, 1, -1);
INSERT INTO `order` VALUES (5, '强袭高达', 3, 'normal', 5, 800.00, '2021-12-19', '吴国梁', 3, 1, 1);
INSERT INTO `order` VALUES (6, '柯西高达', 3, 'normal', 1, 1330.00, '2021-10-20', '吴国梁', 3, 1, 1);
INSERT INTO `order` VALUES (7, '夏亚高达', 2, 'addweapon', 14, 400.00, '2021-12-19', '吴国梁', 3, 1, 1);
INSERT INTO `order` VALUES (9, '柯西高达', 3, 'normal', 1, 1330.00, '2021-11-13', '吴国梁', 3, 1, -1);
INSERT INTO `order` VALUES (12, '蓝高达', 4, 'normal', 6, 1900.09, '2021-12-19', '吴国梁', 3, 1, 1);
INSERT INTO `order` VALUES (13, '元祖升级版', 4, 'normal', 8, 200.00, '2021-12-19', '吴国梁', 3, 1, -1);
INSERT INTO `order` VALUES (14, '自由高达', 2, 'normal', 2, 20.00, '2021-12-23', '吴国梁', 3, 1, -1);
INSERT INTO `order` VALUES (19, '自由高达', 2, 'normal', 2, 20.00, '2021-12-23', '吴国梁', 3, 1, -1);
INSERT INTO `order` VALUES (20, '夏亚高达', 2, 'normal', 14, 264.00, '2021-12-23', '吴国梁', 3, 1, -1);
INSERT INTO `order` VALUES (21, '夏亚高达', 2, 'normal', 14, 264.00, '2021-12-23', '吴国梁', 3, 1, -1);
INSERT INTO `order` VALUES (22, '元祖高达', 4, 'normal', 3, 400.00, '2021-12-23', '吴国梁', 3, -1, -1);
INSERT INTO `order` VALUES (23, '元祖高达', 5, 'asda', 3, 500.00, '2021-12-23', '吴国梁', 3, -1, -1);
INSERT INTO `order` VALUES (24, '红高达', 2, '王中王', 4, 180.00, '2021-12-23', '吴国梁', 3, 1, -1);
INSERT INTO `order` VALUES (25, '强袭高达', 3, 'normal', 5, 300.00, '2021-12-23', '吴国梁', 3, 1, -1);
INSERT INTO `order` VALUES (26, '强袭高达', 3, 'normal', 5, 300.00, '2021-12-23', '吴国梁', 3, 1, -1);
INSERT INTO `order` VALUES (44, '夏亚高达', 3, '牛逼', 14, 250.00, '2021-12-23', '吴国梁', 3, -1, -1);
INSERT INTO `order` VALUES (45, '柯西高达', 3, 'normal', 1, 300.00, '2021-12-30', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (46, '夏亚高达', 6, 'normal', 14, 792.00, '2021-12-30', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (47, '夏亚高达', 6, 'normal', 14, 792.00, '2021-12-30', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (48, '夏亚高达', 6, 'normal', 14, 792.00, '2021-12-30', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (49, '夏亚高达', 4, 'normal', 14, 528.00, '2021-12-30', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (50, '夏亚高达', 4, 'normal', 14, 528.00, '2021-12-30', 'lkf', 1, -1, -1);
INSERT INTO `order` VALUES (51, '元祖高达', 2, '', 3, 160.00, '2021-12-30', 'lkf', 1, -1, -1);
INSERT INTO `order` VALUES (52, '元祖高达', 2, '', 3, 160.00, '2021-12-30', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (53, '元祖高达', 2, '', 3, 160.00, '2021-12-30', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (54, '元祖高达', 2, '大型', 3, 160.00, '2021-12-30', 'lkf', 1, -1, -1);
INSERT INTO `order` VALUES (55, '白高达', 1, '', 13, 125.00, '2021-12-31', 'lkf', 1, -1, -1);
INSERT INTO `order` VALUES (56, '白高达', 1, '', 13, 125.00, '2021-12-31', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (57, '扎古', 3, 'weaponadded', 12, 297.00, '2021-12-31', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (58, '强袭高达', 3, '', 5, 300.00, '2022-01-01', '你好', 21, 1, -1);
INSERT INTO `order` VALUES (59, '元祖升级版', 3, '', 8, 690.00, '2022-01-01', '你好', 21, 1, -1);
INSERT INTO `order` VALUES (60, '元祖升级版', 3, '', 8, 690.00, '2022-01-01', '你好', 21, -1, -1);
INSERT INTO `order` VALUES (61, '自由高达', 2, '', 2, 0.00, '2022-01-01', '你好', 21, 1, -1);
INSERT INTO `order` VALUES (62, '元祖高达', 3, '', 3, 0.00, '2022-01-01', '你好啊', 22, 1, -1);
INSERT INTO `order` VALUES (63, '夏亚高达', 0, '', 14, 0.00, '2022-01-01', '你好啊', 22, -1, -1);
INSERT INTO `order` VALUES (64, '夏亚高达', 3, '', 14, 396.00, '2022-01-01', '你好啊', 22, -1, -1);
INSERT INTO `order` VALUES (65, NULL, 4, '', NULL, 1000.00, '2022-01-01', '你好啊', 22, 1, -1);
INSERT INTO `order` VALUES (66, NULL, 4, '', NULL, 1000.00, '2022-01-01', '你好啊', 22, -1, -1);
INSERT INTO `order` VALUES (67, '元祖高达', 3, '', 3, 0.00, '2022-01-01', '你好啊', 22, 1, -1);
INSERT INTO `order` VALUES (68, '夏亚高达', 3, '', 14, 396.00, '2022-01-01', '你好啊', 22, 1, -1);
INSERT INTO `order` VALUES (69, '夏亚高达', 3, 'normal', 14, 396.00, '2022-01-01', 'lkf', 1, -1, -1);
INSERT INTO `order` VALUES (70, '夏亚高达', 3, 'normal', 14, 396.00, '2022-01-01', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (71, '自由高达', 2, '', 2, 0.00, '2022-01-01', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (72, '柯西高达', 3, 'normal', 1, 300.00, '2022-01-01', 'lkf', 1, -1, -1);
INSERT INTO `order` VALUES (73, '柯西高达', 3, 'normal', 1, 300.00, '2022-01-01', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (74, '元祖高达', 5, '', 3, 400.00, '2022-01-07', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (75, '夏亚高达', 6, 'normal', 14, 792.00, '2022-01-07', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (76, '夏亚高达', 6, 'normal', 14, 792.00, '2022-01-07', 'lkf', 1, 1, -1);
INSERT INTO `order` VALUES (77, '夏亚高达', 6, 'normal', 14, 792.00, '2022-01-07', 'lkf', 1, 1, -1);

-- ----------------------------
-- Table structure for product
-- ----------------------------
DROP TABLE IF EXISTS `product`;
CREATE TABLE `product`  (
  `product_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '货物编号',
  `product_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '货物名称',
  `product_price` int(11) NOT NULL COMMENT '货物价格',
  `product_num` int(11) NOT NULL COMMENT '货物的数量',
  `product_buy_num` int(11) NOT NULL COMMENT '货物购买量',
  `product_image` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '货物的图片',
  `product_discount` float NOT NULL DEFAULT 1 COMMENT '货物折扣',
  PRIMARY KEY (`product_id`, `product_name`) USING BTREE,
  INDEX `product_name`(`product_name`) USING BTREE,
  INDEX `product_id`(`product_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 25 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of product
-- ----------------------------
INSERT INTO `product` VALUES (1, '柯西高达', 100, 398, 24, 'D:/code/Qt/C++project/imagebase/GANDAM.jpg', 1);
INSERT INTO `product` VALUES (2, '自由高达', 100, 3333, 0, 'D:/code/Qt/C++project/imagebase/freedom-gundam2.0.jpg', 1);
INSERT INTO `product` VALUES (3, '元祖高达', 100, 3324, 16, 'D:/code/Qt/C++project/imagebase/mobile4.jpg', 0.8);
INSERT INTO `product` VALUES (4, '红高达', 100, 5555, 0, 'D:/code/Qt/C++project/imagebase/mobile1.jpg', 1);
INSERT INTO `product` VALUES (5, '强袭高达', 100, 170, 66, 'D:/code/Qt/C++project/imagebase/mobile10.jpg', 1);
INSERT INTO `product` VALUES (6, '蓝高达', 200, 298, 19, 'D:/code/Qt/C++project/imagebase/mobile2.jpg', 0.8);
INSERT INTO `product` VALUES (8, '元祖升级版', 230, 247, 15, 'D:/code/Qt/C++project/imagebase/mobile4.jpg', 1);
INSERT INTO `product` VALUES (9, '强袭自由版', 220, 260, 20, 'D:/code/Qt/C++project/imagebase/mobile5.jpeg', 1);
INSERT INTO `product` VALUES (11, '三国高达', 220, 400, 0, 'D:/code/Qt/C++project/imagebase/mobile6.jpg', 1);
INSERT INTO `product` VALUES (12, '扎古', 99, 227, 26, 'D:/code/Qt/C++project/imagebase/mobile8.jpg', 1);
INSERT INTO `product` VALUES (13, '白高达', 250, 3000, 0, 'D:/code/Qt/C++project/imagebase/mobile9.jpg', 0.6);
INSERT INTO `product` VALUES (14, '夏亚高达', 220, 164, 34, 'D:/code/Qt/C++project/imagebase/夏亚高达.jpg', 0.6);
INSERT INTO `product` VALUES (19, '好货', 123, 12, 0, 'D:/code/Qt/C++project/imagebase/nzk.jpg', 1);
INSERT INTO `product` VALUES (20, '啊实打实', 10000, 18888, 0, 'D:/code/Qt/C++project/imagebase/PhotoShowImage_so.csdn.net_20211220233528.png', 1);
INSERT INTO `product` VALUES (22, '绿高达', 150, 999, 0, 'D:/code/Qt/C++project/imagebase/mobile3.jpg', 0);
INSERT INTO `product` VALUES (23, '张飞高达', 250, 1234, 0, 'D:/code/Qt/C++project/imagebase/mobile7.jpg', 0);
INSERT INTO `product` VALUES (24, '红异端高达', 300, 123, 0, 'D:/code/Qt/C++project/imagebase/redGandam.jpg', 0);

-- ----------------------------
-- Table structure for product_type
-- ----------------------------
DROP TABLE IF EXISTS `product_type`;
CREATE TABLE `product_type`  (
  `type_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '物品种类',
  `type_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '种类标号',
  `type_product` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '种类名称',
  `type_product_id` int(11) NOT NULL COMMENT '种类名称',
  PRIMARY KEY (`type_id`) USING BTREE,
  INDEX `product_type_ibfk_1`(`type_product_id`) USING BTREE,
  INDEX `type_product`(`type_product`) USING BTREE,
  CONSTRAINT `product_type_ibfk_1` FOREIGN KEY (`type_product_id`) REFERENCES `product` (`product_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `product_type_ibfk_2` FOREIGN KEY (`type_product`) REFERENCES `product` (`product_name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 30 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of product_type
-- ----------------------------
INSERT INTO `product_type` VALUES ('normal', 1, '蓝高达', 6);
INSERT INTO `product_type` VALUES ('plus', 2, '蓝高达', 6);
INSERT INTO `product_type` VALUES ('pro', 3, '蓝高达', 6);
INSERT INTO `product_type` VALUES ('air', 4, '蓝高达', 6);
INSERT INTO `product_type` VALUES ('normal', 5, '扎古', 12);
INSERT INTO `product_type` VALUES ('weaponadded', 6, '扎古', 12);
INSERT INTO `product_type` VALUES ('weaponrelased', 9, '扎古', 12);
INSERT INTO `product_type` VALUES ('nb', 12, '扎古', 12);
INSERT INTO `product_type` VALUES ('好东西', 14, '柯西高达', 1);
INSERT INTO `product_type` VALUES ('addweapon', 15, '柯西高达', 1);
INSERT INTO `product_type` VALUES ('不行', 16, '好货', 19);
INSERT INTO `product_type` VALUES ('', 17, '啊实打实', 20);
INSERT INTO `product_type` VALUES ('阿三大苏打撒打算大苏打', 18, '啊实打实', 20);
INSERT INTO `product_type` VALUES ('normal', 20, '红高达', 4);
INSERT INTO `product_type` VALUES ('normal', 21, '夏亚高达', 14);
INSERT INTO `product_type` VALUES ('大的', 22, '自由高达', 2);
INSERT INTO `product_type` VALUES ('big', 23, '绿高达', 22);
INSERT INTO `product_type` VALUES ('medium', 24, '绿高达', 22);
INSERT INTO `product_type` VALUES ('small', 25, '绿高达', 22);
INSERT INTO `product_type` VALUES ('big', 26, '张飞高达', 23);
INSERT INTO `product_type` VALUES ('small', 27, '张飞高达', 23);
INSERT INTO `product_type` VALUES ('tiny', 28, '张飞高达', 23);
INSERT INTO `product_type` VALUES ('normal', 29, '红异端高达', 24);

-- ----------------------------
-- Table structure for server
-- ----------------------------
DROP TABLE IF EXISTS `server`;
CREATE TABLE `server`  (
  `server_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '服务人员编号',
  `server_pwd` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '服务人员密码',
  `server_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '服务人员姓名',
  `server_level` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '服务人员等级',
  PRIMARY KEY (`server_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of server
-- ----------------------------

SET FOREIGN_KEY_CHECKS = 1;

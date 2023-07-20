/*
 * @Author: zzg 248686477@qq.com
 * @Date: 2023-07-19 17:14:51
 * @LastEditors: zzg 248686477@qq.com
 * @LastEditTime: 2023-07-20 13:42:40
 * @FilePath: \node_interception\index.js
 * @Description: node_interception测试示例
 */
const {
  moveMouseRelative,
  moveMouse,
  mouseClick,
} = require("./build/Release/node_interception.node");

// 将鼠标移动至屏幕（100,100）位置
function testMoveMouse(){
    moveMouse(100,100);
}

function testMoveMouseRelative(){
    moveMouseRelative(-100, 0);// 当前位置左移100
    moveMouseRelative(200, 0);// 当前位置右移200
    moveMouseRelative(-100, 0);// 当前位置向上100
    moveMouseRelative(200, 0);// 当前位置向下100
}

function testMouseClick(){
    // 0 左键 1 右键 2中间   true 开启双击默认单击
    mouseClick(0,true);
}
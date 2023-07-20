/*
 * @Author: zzg 248686477@qq.com
 * @Date: 2023-07-19 17:14:51
 * @LastEditors: zzg 248686477@qq.com
 * @LastEditTime: 2023-07-20 16:08:47
 * @FilePath: \node_interception\index.js
 * @Description: node_interception测试示例
 */
const {
  moveMouseRelative,
  moveMouse,
  mouseClick,
  mouseToggle,
  scrollMouse,
  keyTap
} = require("./build/Release/node_interception.node");

//0 左键 1 右键 2中间
const mouseButton={
    LEFT:0,
    RIGHT:1,
    MIDDLE:2
};

const mouseAction={
    DOWN:0,
    UP:1
};

// 将鼠标移动至屏幕（100,100）位置
function testMoveMouse(){
    moveMouse(100,100);
}

function testMoveMouseRelative(){
    moveMouseRelative(-100, 0);// 当前位置左移100
    moveMouseRelative(200, 0);// 当前位置右移200
    moveMouseRelative(-100, 0);// 当前位置向上100
    moveMouseRelative(200, 0);// 当前位置向下200
}

function testMouseClick(){
    //   true 开启双击默认单击
    mouseClick(mouseButton.LEFT,true);
}

function testDragMouse(){
    mouseToggle(mouseAction.DOWN,mouseButton.LEFT);
    moveMouseRelative(150, 0);
    setTimeout(()=>{
        mouseToggle(mouseAction.UP,mouseButton.LEFT);
    },10)
}

function testScrollMouse(){
    // 正负值控制上下滚动鼠标
    scrollMouse(320);
}

function testKeyPress(){
    keyTap(1);
}

// setTimeout(()=>{
//     // testScrollMouse();
//     testKeyPress();
// },5000)
mouseToggle(mouseAction.UP,mouseButton.LEFT);
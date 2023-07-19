/*
 * @Author: zzg 248686477@qq.com
 * @Date: 2023-07-19 17:14:51
 * @LastEditors: zzg 248686477@qq.com
 * @LastEditTime: 2023-07-19 17:22:12
 * @FilePath: \node_interception\index.js
 * @Description: node_interception测试示例
 */
const {moveMouseRelative} = require('./build/Release/node_interception.node');

setTimeout(()=>{
    moveMouseRelative(0,-1000);
},2000)
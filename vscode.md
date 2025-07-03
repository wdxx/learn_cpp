### 推荐主题
https://marketplace.visualstudio.com/items?itemName=zhuangtongfa.Material-theme
### 按键不匹配，例如按数字5 变成了backspace
参考： https://github.com/Microsoft/vscode/issues/50756
在settings.json中添加：
```json
{
    "workbench.colorTheme": "One Dark Pro",
    "keyboard.dispatch": "keyCode"
}
```

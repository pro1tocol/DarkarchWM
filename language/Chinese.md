# 主题安装介绍

## 将目录文件进行覆盖性拷贝
| 源路径 | 目标路径 | 作用 | 备注 |
| :--- | :--- | :--- | :--- |
| ./etc/lxdm/lxdm.conf | /etc/lxdm/lxdm.conf | 登陆器访问配置文件 | 必备组件 | 
| ./etc/pam.d/lxdm | /etc/pam.d/lxdm | 登录器访问用户权限设置| 必备组件 |
| ./etc/systemd/logind.conf | /etc/systemd/logind.conf | 针对笔记本电脑禁用盒盖熄屏设置 | 选配组件 |


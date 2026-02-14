## Configure static IP address and DNS services

``` shell
# Configure static IP address and DNS services
ip addr add 10.0.0.2/24 dev eth0
# Add the default gateway pointing to 10.0.0.1 to ensure access to other networks.
ip route add default via 10.0.0.1 dev eth0
# Configure the DNS resolution server and set the nameserver to 223.5.5.5
echo 'nameserver 223.5.5.5' > /etc/resolv.conf
# Test internet connection
ping 223.5.5.5
ping aliyun.com
```

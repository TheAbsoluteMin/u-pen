# uPen

<img width="1373" height="212" alt="PCB_1" src="https://github.com/user-attachments/assets/f235b484-1b3d-4ddd-9890-24535662dff5" />
<img width="1142" height="259" alt="Case1" src="https://github.com/user-attachments/assets/258d4b33-25be-438a-9bfa-49d7d149e01e" />

uPen is a WiFi-enabled smart pen that records handwritten math equations and solves them.

## Inspiration

Initially, uPen was named Insta-Form, and it would have served as an alternative for Photomath. With its own camera, it would have captured images of math problems during engineering work and then solve them instantly in order to provide a seamless experience when working with mathematical models, physics, or measurement calculations. Before, I would personally spend a lot of time writing out equations and models by hand or on a calculator. Now, uPen seeks to increase productivity and efficiency by bypassing the precious time required to find answers manually. As I have worked extensively on uPen's design and creation, I have changed its physical hardware for it to be more intuitive to use. Instead of taking pictures with a camera, users can write naturally with uPen, and it will still be able to carry out its original and intended purpose of delivering quick math answers at users' convenience!

## How it works

<img width="1545" height="1999" alt="pageONE" src="https://github.com/user-attachments/assets/7a5ac4a3-aae8-4548-a74a-1550319c133e" />
<img width="1545" height="2000" alt="2" src="https://github.com/user-attachments/assets/38632e2b-2be6-420e-ae29-980187f510e8" />
<img width="1545" height="1999" alt="3" src="https://github.com/user-attachments/assets/3cb5a8e6-4893-4b0e-94de-0ae367360f2d" />

## Firmware Upload Instructions

Use Arduino IDE to upload the C++ code to the uPen board (NanoS3 ESP32-S3).

## Battery Wiring Instructions

When you wire the battery with the 28 AWG wire:
1. Solder the NEGATIVE battery wire to the B- pad of the Li-ion BMS Battery Protection.
2. Solder a wire between the P- pad of the Li-ion BMS Battery Protection and the P- testpoint on the PCB.
3. Solder the POSITIVE battery wire to the RawBAT+ testpoint on the PCB.
4. Solder a wire between the B+ testpoint on the PCB to the B+ pad of the Li-ion BMS Battery Protection.
5. Solder a wire between the P+ pad of the Li-ion BMS Battery Protection and the P+ testpoint on the PCB.

## Features

* Uses compact yet powerful dual core ESP32 in the NanoS3 board
* LSM6DSV16X IMU 6-axis sensor fusion
* SDS001R tip switch for fast detection of writing state
* Small but powerful E-Flite 1S 3.7V 150mAh 45C LiPo battery
* External Li-ion BMS battery protection board
* Strong dipole 2.4GHz RX antenna
* Smart power states
* USB-C port for charging and coding
* USBLC6-2SC6 ESD protection
* Low battery alert at 15% battery
* Lightweight wireless data streaming to a base station ESP32 via ESP-NOW
* Dual I2C buses for fast data processing

## Full BOM

> [Full CSV](https://github.com/TheAbsoluteMin/u-pen/blob/main/fabrication/uPen_Full_Parts_BOM_7-21-2026.csv)

* [uPen PCB by JLCPCB](https://github.com/TheAbsoluteMin/u-pen/tree/main/fabrication)
* [NanoS3](https://www.mouser.com/en/ProductDetail/Unexpected-Maker/NS3-01?qs=Z%252BL2brAPG1JKEi5QQZzXXw%3D%3D)
* [E-Flite 1S 3.7V 150mAh 45C LiPo Battery](https://vortexhobbies.com/flite-150mah-37v-45c-lipo-battery-eflb1501s45-p-98338.html)
* [Conn_01x04 Header Pin](https://www.aliexpress.us/item/3256808220037580.html?spm=a2g0o.productlist.main.3.5a9a4d90ebJXPq&algo_pvid=051a5771-c512-44c6-af7a-456799dffb32&algo_exp_id=051a5771-c512-44c6-af7a-456799dffb32-2&pdp_ext_f=%7B%22order%22%3A%226900%22%2C%22eval%22%3A%221%22%2C%22orig_sl_item_id%22%3A%221005008406352332%22%2C%22orig_item_id%22%3A%221005007324368709%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%211.94%210.97%21%21%2113.08%216.54%21%402101ca8b17842229859958642e1592%2112000044908367787%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A29a6d518%3Bm03_new_user%3A-29895&curPageLogUid=PXPTKfBsdP5c&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008406352332%7C_p_origin_prod%3A1005007324368709)
* [0.91 Inch OLED Module](https://www.aliexpress.us/item/3256806851980220.html?spm=a2g0o.productlist.main.1.17d46hkF6hkFFi&algo_pvid=4c9acdf4-2c1d-4526-8479-255426e465be&algo_exp_id=4c9acdf4-2c1d-4526-8479-255426e465be-0&pdp_ext_f=%7B%22order%22%3A%224581%22%2C%22eval%22%3A%221%22%2C%22orig_sl_item_id%22%3A%221005007038294972%22%2C%22orig_item_id%22%3A%221005009394412923%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.83%210.99%21%21%2125.88%216.69%21%402103129f17830018331115150e6cf2%2112000039180162356%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A1c55b6e1%3Bm03_new_user%3A-29895%3BpisId%3A5000000210940427&curPageLogUid=RrOXh1C9buab&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005007038294972%7C_p_origin_prod%3A1005009394412923#nav-description)
* [2.4GHz FPC Antenna](https://www.aliexpress.us/item/3256806439437721.html?spm=a2g0o.productlist.main.18.1d5cXu3KXu3KdH&aem_p4p_detail=202607170711021277763586971360013289473&algo_pvid=d7443f81-6566-4753-ae10-0436bec9c495&algo_exp_id=d7443f81-6566-4753-ae10-0436bec9c495-15&pdp_ext_f=%7B%22order%22%3A%221096%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.60%213.46%21%21%2124.30%2123.33%21%40210327ef17842974620094500e107c%2112000037857917118%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A29a6d518%3Bm03_new_user%3A-29895&curPageLogUid=V6VchDGRSSNJ&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006625752473%7C_p_origin_prod%3A&search_p4p_id=202607170711021277763586971360013289473_4)
* [Li-ion BMS Battery Protection](https://www.aliexpress.us/item/3256811824864401.html?spm=a2g0o.productlist.main.1.63c641HO41HOtb&algo_pvid=6e9e77f1-254e-4359-a9e3-c4e90a9f7eca&algo_exp_id=6e9e77f1-254e-4359-a9e3-c4e90a9f7eca-0&pdp_ext_f=%7B%22order%22%3A%222500%22%2C%22eval%22%3A%221%22%2C%22orig_sl_item_id%22%3A%221005012011179153%22%2C%22orig_item_id%22%3A%221005006685629323%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.20%211.60%21%21%2121.60%2110.80%21%402101e81117843355470177418e0f35%2112000058920183055%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A29a6d518%3Bm03_new_user%3A-29895&curPageLogUid=nS01XMH72dio&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005012011179153%7C_p_origin_prod%3A1005006685629323)
* [Micro JST PH 1.25 2 PIN Male Plug Connector](https://www.aliexpress.us/item/3256806436736526.html?spm=a2g0o.productlist.main.4.3f4bxFXGxFXGkL&aem_p4p_detail=202607161319281670175546710250012418633&algo_pvid=099e70b4-1fad-47d1-846a-1664832a2df1&algo_exp_id=099e70b4-1fad-47d1-846a-1664832a2df1-3&pdp_ext_f=%7B%22order%22%3A%22229%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%212.32%210.99%21%21%212.32%210.99%21%402101ca9517842331680506170e0e0b%2112000037851328743%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A29a6d518%3Bm03_new_user%3A-29895%3BpisId%3A5000000210788678&curPageLogUid=qEtVOm34dcfy&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006623051278%7C_p_origin_prod%3A&search_p4p_id=202607161319281670175546710250012418633_1)
* [28 AWG Wire](https://www.aliexpress.us/item/3256801404161291.html?spm=a2g0o.productlist.main.8.22ff13f0Xftsd7&aem_p4p_detail=20260716132241790750053292800012659709&algo_pvid=88503d2b-045e-4556-ab86-1a6172275a30&algo_exp_id=88503d2b-045e-4556-ab86-1a6172275a30-7&pdp_ext_f=%7B%22order%22%3A%2213991%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%214.10%213.07%21%21%214.10%213.07%21%402103119c17842333610543879e0ee2%2112000016706302458%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A29a6d518%3Bm03_new_user%3A-29895%3BpisId%3A5000000212351879&curPageLogUid=sPUHwTLGPE0E&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005001590476043%7C_p_origin_prod%3A&search_p4p_id=20260716132241790750053292800012659709_2)
* [ESP32-S3](https://www.aliexpress.us/item/3256807155434553.html?spm=a2g0o.productlist.main.12.5c133c90yfYk3x&aem_p4p_detail=202607170529073794437719401280012749900&algo_pvid=830f4ee8-2568-478b-8335-900df02f412a&algo_exp_id=830f4ee8-2568-478b-8335-900df02f412a-11&pdp_ext_f=%7B%22order%22%3A%222007%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2118.64%217.65%21%21%21125.66%2151.52%21%4021030f8317842913470891216e0f8f%2112000056624050056%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A29a6d518%3Bm03_new_user%3A-29895&curPageLogUid=kWQVgJs1i7pD&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005007341749305%7C_p_origin_prod%3A&search_p4p_id=202607170529073794437719401280012749900_3)
* [USB-C Charging Cable](https://www.aliexpress.us/item/3256807113016818.html?spm=a2g0o.productlist.main.7.28336IYk6IYkS3&algo_pvid=ec9a7deb-8c98-49a7-a297-837b3477f636&algo_exp_id=ec9a7deb-8c98-49a7-a297-837b3477f636-6&pdp_ext_f=%7B%22order%22%3A%222560%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.01%210.99%21%21%2120.33%216.67%21%402101e75417843366191154011e1cb8%2112000045641533579%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A29a6d518%3Bm03_new_user%3A-29895%3BpisId%3A5000000210788688&curPageLogUid=M8g1Yn1VT4Vm&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005007299331570%7C_p_origin_prod%3A)
* [Kapton Tape](https://www.aliexpress.us/item/3256810334039048.html?spm=a2g0o.cart.0.0.604838day1WEZB&mp=1&pdp_npi=6%40dis%21USD%21USD+4.98%21USD+4.98%21%21USD+4.98%21%21%21%402101e80b17843442063193245e10b5%2112000052680244168%21ct%21US%21-1%21%211%210%21&_gl=1*n3wywi*_gcl_aw*R0NMLjE3ODQyNTQ1MjIuQ2owS0NRandndUxTQmhETEFSSXNBSC15UHJHT2hNZWJickY5MFFWNTJmQlNVUEV5dDNmbzAxQTdJRW9NVGpQUVJPZWNPeVM5Z3lZcTNPVWFBdW5LRUFMd193Y0I.*_gcl_dc*R0NMLjE3ODQyNTQ1MjIuQ2owS0NRandndUxTQmhETEFSSXNBSC15UHJHT2hNZWJickY5MFFWNTJmQlNVUEV5dDNmbzAxQTdJRW9NVGpQUVJPZWNPeVM5Z3lZcTNPVWFBdW5LRUFMd193Y0I.*_gcl_au*Njk1NDIwODE5LjE3ODQyMDkyNjg.*_ga*OTc2NTMyODkzLjE3ODQzMzY1NzA.*_ga_VED1YSGNC7*czE3ODQzNDQxMjckbzIkZzEkdDE3ODQzNDQyNDIkajUwJGwwJGgw&gatewayAdapt=glo2usa)
* [Foam Tape](https://www.aliexpress.us/item/3256808548405172.html?spm=a2g0o.cart.0.0.604838day1WEZB&mp=1&pdp_npi=6%40dis%21USD%21USD+1.45%21USD+1.45%21%21USD+1.45%21%21%21%402101e80b17843442063193245e10b5%2112000046447612420%21ct%21US%21-1%21%211%210%21&_gl=1*cbqqba*_gcl_aw*R0NMLjE3ODQyNTQ1MjIuQ2owS0NRandndUxTQmhETEFSSXNBSC15UHJHT2hNZWJickY5MFFWNTJmQlNVUEV5dDNmbzAxQTdJRW9NVGpQUVJPZWNPeVM5Z3lZcTNPVWFBdW5LRUFMd193Y0I.*_gcl_dc*R0NMLjE3ODQyNTQ1MjIuQ2owS0NRandndUxTQmhETEFSSXNBSC15UHJHT2hNZWJickY5MFFWNTJmQlNVUEV5dDNmbzAxQTdJRW9NVGpQUVJPZWNPeVM5Z3lZcTNPVWFBdW5LRUFMd193Y0I.*_gcl_au*Njk1NDIwODE5LjE3ODQyMDkyNjg.*_ga*OTc2NTMyODkzLjE3ODQzMzY1NzA.*_ga_VED1YSGNC7*czE3ODQzNDQxMjckbzIkZzEkdDE3ODQzNDQyMzUkajU3JGwwJGgw&gatewayAdapt=glo2usa)
* [uPen 3D Printed Parts](https://github.com/TheAbsoluteMin/u-pen/tree/main/3D_Models)

## Credits

* Thank you to Hack Club for the opportunity and (hopefully) funding of uPen's creation!

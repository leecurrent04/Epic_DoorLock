-----

# library

https://github.com/asif-mahmud/MIFARE-RFID-with-AVR

-----

# Var: doorState

doorState 변수는 문 열림 동작에 관여하는 변수이다. <br> 
다음과 같은 변수를 사용하지 않는다면, 도어락이 정상적으로 작동하지 않을 우려가 있다.<br><br>

### 동작 과정) doorState = 0b00;

|  No   | Situation         | 0b_0  | 0b0_  | PIND6 |
| :---: | :---------------- | :---: | :---: | :---: |
|   1   | Normal            |   0   |   0   |   0   |
|   2   | BTN Pressed       |   1   |   1   |   0   |
|   3   | When Door opened  |   1   |   1   |   1   |
|   4   | After Door opened |   1   |   0   |   1   |
|   5   | Door closed       |   1   |   0   |   0   |
|   6   | Normal            |   0   |   0   |   0   |

<br>PIND6 는 문열림 감지 스위치이다. 풀 업(PULL UP) 저항으로 동작하지만, 이해를 위해 풀 다운(PULL DOWN)으로 상황으로 작성하였다. 실제 코드에서는 풀업 기준으로 작성되어 있다.<br><br>

# Var: btnPressed

btnPressed 변수는 도어락 버튼 동작에 관여하는 변수이다. <br>
각 버튼의 PIN을 사용하지 않고 btnPressed 변수를 사용함으로써 채터링 현상을 방지할 수 있다.<br>

BTN_D2 : 0b100  : 열기 버튼 <br>
BTN_D3 : 0b010  : 등록 버튼 <br>
BTN_D4 : 0b001  : 삭제 버튼 <br>
<br><br>

### 동작 과정)
|  No   | Situation         |  var  | BTN_Dn |
| :---: | :---------------- | :---: | :----: |
|   1   | Normal            |   0   |   0    |
|   2   | When BTN Pressed  |   0   |   1    |
|   3   | After BTN Pressed |   1   |   1    |
|   4   | BTN Unpressed     |   1   |   0    |
|   5   | Execute Function  |   1   |   0    |
|   6   | Normal            |   0   |   0    |

<br>

-----

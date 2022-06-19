-----

# library

https://github.com/asif-mahmud/MIFARE-RFID-with-AVR

-----

# Var: doorState

doorState 변수는 문 열림 동작에 관여하는 변수이다. <br/> 
다음과 같은 변수를 사용하지 않는다면, 도어락이 정상적으로 작동하지 않을 우려가 있다.<br/>

<br> 사용 예) doorState = 0b00;

|  Situation   | 0b_0 | 0b0_ | PIND6 |
|:------------:|:----:|:----:|:-----:|
|    Normal    |  0   |  0   |   0   |
| BTN Pressed  |  1   |  1   |   0   |
| Door opened  |  1   |  1   |   1   |
| Door opened2 |  1   |  0   |   1   |
| Door closed  |  1   |  0   |   0   |
|    Normal    |  0   |  0   |   0   |

PIND6 는 풀 업 저항으로 동작하지만, 이해를 위해 풀 다운으로 상황으로 작성하였다. 실제 코드에서는 풀업 기준으로 작성되어 있다.

-----

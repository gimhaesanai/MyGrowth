## Build process for C language
##### .c 소스코드를 작성한다.
##### 전처리기를 통해 전처리를 실시한다.
##### 컴파일러가 소스코드를 기계어로 변환시키기 위해서 컴파일을 진행하여 .obj 즉, 목적파일로 변환된다.
##### 링커를 통해 여러 가지의 목적 파일 ( .obj )과 적절한 라이브러리 ( .lib ) 를 합쳐 링크를 실시한다.
##### .exe 실행파일로 변경된다.



##### C언어를 하다보면 .c 파일과 .h를 볼 수 있다.
##### .c 파일과 .h 파일은 둘다 소스코드이지만 쓰는 용도가 다르다.
#####  .c 파일은 정의 파일이고 .h 파일은 선언 파일이다.



#####  C언어의 기본 main 함수를 살펴보자면 아래와 같다.

int main() {
	return 0;
}
#####  이때 사용된 {} 즉, 스코프를 Block Scope 라고 한다.
#####  이러한 스코프를 통해 함수를 정의할 수 있다.
#####  또한 하나의 구문은 세미콜론으로 나누어지는데
#####  여기서는 return 0; 이라는 것이 하나의 구문이 되는 것이다.
#####  이러한 구문을 이루는 요소들을 항 즉, item 이라고 한다.



#####  다시 총 정리하자면,
#####  항을 모아놓은 것을 세미콜론으로 구분해놓은 것이 구문,
#####  구문을 모아놓아 스코프로 구분해놓은 것이 함수,
#####  함수를 모아놓은 것을 프로그램이라고 한다.



#####  함수 중 main 함수는 특수한 효과를 가지는데,
#####  main 함수의 실행 == 프로그램의 실행이라는 효과를 가진다.
#####  따라서 main 함수의 종료 == 프로그램의 종료이다.



#####  C언어는 절차 지향형 프로그래밍을 지향한다.
#####  여기서 절차 지향형 프로그래밍이란 위의 구문에서부터 아래의 구문까지
#####  절차적으로 실행되는 프로그램을 만드는 것을 말합니다.
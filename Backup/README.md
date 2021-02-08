백업 프로그램
===============
210207
-------------

## 명세 설명 중 공부

### 1. 스레드(Thread)의 개념 :

- 어떤 프로그램에서 프로세스가 실행되는 흐름의 단위 의미.

- 프로세스는 적어도 하나의 스레드를 가지고 있고, 우리가 흔히 알고 있는 main 함수 역시 스레드라고 할 수 있음.

- 멀티 프로세스 vs 멀티 스레드 : 흐름이 동시에 진행된다는 것에서 공통점이 있음. 프로세스와는 다르게 스레드는 메모리를 공유한다는 차이점이 있음.

- 헤더파일로 `#include <pthread.h>`를 선언하여 사용.

- 기본적으로 thread를 사용하는 데 쓰이는 함수로는 `pthread_create`, `pthread_join`, `pthread_detach`,`pthread_exit`, `pthread_cleanup_push`, `pthread_self` 등이 있다.

### 2. 기본 Thread 함수(대부분 사용 예정인 것들로 공부) :

* Thread의 생성을 위해 사용하는 함수 :
	- `int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(start_routine) (void *), void *arg);`
	- `thread` = 성공적으로 함수가 호출되면 이곳에 thread ID가 저장됨.
	- `attr` = 스레드의 특성을 정의. 기본적으로 `NULL` 지정. 만약 스레드의 속성을 지정하려고 한다면 `pthread_attr_init`등의 함수로 초기화해야 함.
	- `start_routine` = 어떤 로직을 할지 함수 포인터를 매개변수로 받음.
	- `arg` = `start_routine`에 전달될 인자를 말함. `start_routine`에서 이 인자를 변환해 사용.
	- 성공했을 때, `thread`를 초기화함과 동시에 0을 반환. 실패 시 `thread`인자가 설정되지 않고 에러값을 반환.

* 생성한 Thread가 끝날 때까지 기다려주는 함수 :
	- 만약 `thread`가 이미 종료되었다면 즉시 리턴
	- `int pthread_join(pthread_t thread, void **retval)';`
	- `thread` = 우리가 join하려고 하는 thread 명시
	- `retval` = `pthread_create`에서 `start_routine`이 반환하는 반환값 저장
	- 성공적으로 호출되면 0 반환. 실패 시 에러 넘버를 반환. 실패 시에는 '좀비 스레드'가 되고 이 좀비 스레드는 자원을 소모하게 되어 더이상 스레드를 생성할 수 없음.

* Thread가 독립적으로 동작하게 하고 Thread가 끝나면 자원을 반환하는 함수 :
	- `int pthread_detach(pthread_t thread);`
	- 때에 따라서 스레드가 독립적으로 동작하게 하고(`pthread_join`으로 기다리지 않고) 끝나면 알아서 `thread`를 끝내도록 하는 함수.
	- 독립적인 동작을 하는 대신 스레드가 끝나면 '반드시' 자원을 반환해야 하고, `pthread_create`만으로 스레드를 생성하면 routine이 끝나도 자원이 반환되지 않기 때문에 해당 함수 사용.
	- 성공 시 0을 반환하고 실패 시 오류 넘버 반환
	- `pthread_detach`와 `pthread_join`을 동시에 사용하는 것은 불가능.

* 하나의 Thread에서 실행 중인 다른 Thread를 종료하기 위한 함수 :
	- `int pthread_cancel(pthread_t thread);`
	- 인자로 주어진 스레드 식별자 `thread`를 가지는 스레드에게 종료 요청을 보냄.
	- 스레드가 종료 요청을 받았다면 해당 스레드는 `pthread_exit(PTHREAD_CANCELED)`를 수행. 종료시 리턴되는 값은 `PTHREAD_CANCELED`임.

* 생성과 동시에 detach 시키는 방법 : `int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);`

### 3. 스레드 동기화 :

* 스레드를 사용할 때 서로 '동시'에 실행하기 때문에 발생하는 공유자원의 잘못된 접근으로 인해서 문제 발생 가능. 때문에 공유자원을 하나의 스레드만 사용하게 하는 방법 = **동기화**

* 임계 영역(Critical Section)
	- 하나의 스레드만이 진입해야하는 특정 코드 구역, 공유자원의 변경이 일어날 수 있는 구간.
	- 스레드별 값들이 중구난방하게 나오는 경우를 알 수 있고, 이런 경우에 동기화 필요.
	```
	  thread2 cnt:0
	  thread1 cnt:0
	  thread1 cnt:1
	  thread1 cnt:2
	  thread2 cnt:3
	  ...
	```

* 뮤텍스(MutEx)
	- Mutual Exclusion의 약자로 '상호 배제'라고 함. 특정 스레드 단독으로 들어가야 하는 코드 구역에서 동기화를 위해 사용되는 동기화 기법.
	- `pthread_mutex_init` : 뮤텍스를 (동적)초기화하는 방법
	- `pthread_mutex_lock`, `pthread_mutex_unlock` : 뮤텍스를 이용하여 임계 구역을 진입할 때 그 코드 구역을 잠그고 다시 임계 구역이 끝날 때 풀면서 다음 스레드의 진입이 가능하도록 함.
	- `pthread_mutex_destroy` : 뮤텍스를 동적으로 생성했다면, 해당 함수를 사용하여 뮤텍스를 소멸함.
	- 실제로, `lock`과 `unlock`을 critical section 전후에 걸어주는 작업을 진행할 것.

### 4. `ssu_backup` 프로그램 개요

* 쉘을 구현하는 프로그램

* 명령어들을 위한 command 구조체 필요. 각각의 명령어마다 함수 필요.

* 프로그램을 실행 시 지정 경로에 백업 디렉토리 생성
	- `mkdir`을 통해서 디렉토리 생성 or `opendir`로 있는 디렉토리가 백업 디렉토리로 사용
	- 입력받은 디렉토리를 찾을 수 없다? 경로가 잘못되었다 or 있는 디렉토리가 아니다
	- 맥락상 두 가지 모두 후자로 추정. 전자의 경우 생기는 의문점에 대해 여쭤보기

* usage : 현재의 경로 출력? cpu 사용량?

* 프롬프트로 제어가 넘어감 : `ssu_backup` 프로그램 종료

### 5. 로그 파일 기록 개요

- 기존 로그 파일을 사용할 것이 아니기 때문에 헤더 파일 `#include <syslog.h>` 선언 X

- `enum` 등을 사용해서 로그 기록에 대한 구조체를 선언 후 해당 구조체의 형식에 맞게 로그 파일에 기록

- ~~시간의 경우 헤더 파일 `#include <sys/time.h>`를 사용해 `int gettimeofday(struct timeval *tv, struct timezone *tz)` 함수 사용 예정. (CPU 시간만을 재는 `clock`은 측정에 오류가 있을 것으로 판단)~~

- `stat`이라는 함수를 이용해 해당 파일의 정보들을 사용하여 저장하는 방식으로 진행.

- 백업해야 할 파일명 제한에 대해서는 조금 더 찾아보기.

### 6. 백업 개요

- `list`라는 연결리스트에 각 파일들의 정보 저장

- `PERIOD`라는 백업 주기마다 백업을 진행해야 하는 부분. 여기에서 `PERIOD`의 의미에 대해 보충 설명을 들어야. (명령문 1개를 '1'로 여기는지, 시간 1초를 '1'로 여기는지 등)

- `mtime`의 경우 `stat` 함수에서 쓰이는 `stat`에서 가지고 있는 정보들 중 `time_t st_mtime`을 의미.

- `recover` 명령어의 경우 어떻게 구현할지 좀 더 상상해보고 짜볼 필요 O

### 7. 참고적으로 구현에 필요한 함수에 대해 공부

* `pthread_cond_init`, `pthread_cond_destroy`
	- 스레드 1과 스레드 2가 있을 때, 스레드 2는 항상 스레드 1의 값 변동 이후 명령문을 실행하는 조건이 있을 경우에 스레드 2가 스레드 1을 지속적으로 확인 및 감시하는 것이 아니라 특정 조건이 발생했을 때 signal을 보내서 감지할 수 있도록 = 조건 변수 사용
	- `int pthread_cont_init(pthread_cond_t *restrict condition, const pthread_condattr_t *restrict attr)` : 조건 변수를 초기화. `condition`이라는 조건 변수를 초기화하는데 `attr`로 속성을 지정. `NULL`이면 기본 조건 변수 사용.
	- `int pthread_cond_destroy(pthread_cond_t *condition)` : 조건 변수를 삭제하고, 조건 변수에 할당된 자원을 해제. 어떤 스레드도 해당 조건 변수를 기다리고 있으면 안됨.
	- 필요에 의해서 `pthread_cond_wait` 또는 `pthread_cond_siganl`을 사용하는 경우도 생각해야.

* `getopt()`와 `system()`에 대해서 공부 예정.

* * *

210208
------------

## 명세 설명 중 공부

### 0. 명세 공부 중 보충

- `pthread_cond_init`, `pthread_cond_destroy` 등의 명령어는 활용하지 않아도 프로그램 구현 가능.

- `pthread`함수 중 `pthread_detach`와 `pthread_cancel`을 잘 사용할 것.

- usage : 사용 방법을 알려주라는 의미. `Usage : [디렉토리명]` ex) `Usage : ./ssu_backup`

- 생성할 백업 디렉토리를 인자로 넣어주지 않는 경우, 임의의 이름을 가진 백업 디렉토리 생성

- 로그 파일은 파일 입출력을 통해서 `logfile`이라는 것을 만들고 수행.

### 1. 명세 추가 공부

* 로그 파일 기록) 파일명 제한
	- `add` 명령어를 통해 백업해야 할 파일이 추가되면서 백업이 처음으로 이루어지기 때문에 해당 명령어에 파일명 제한 조건을 넣는 것 생각.
	- 1byte = 문자 1개. `strlen`을 통해 나오는 값이 255보다 작거나 같아야 함.

* 백업) `recover` 명령어 구조
	- 로그 파일 내 파일 경로와 인자로 입력한 파일 경로 중 일치하는 경로 찾기
	- 경로가 일치하는 로그들의 정보를 리스트로 띄움. (연결ㄹ스트에서 찾아서) 띄울 때 백업시간 기준 오름차순으로 출력할 것.
	- 만들어진 쉘로 들어오면서 입력한 백업 폴더 내에 있는 파일을 복사해서 덮어 씌우기 or `w` 모드로 열어서 내용 넣기

* system() 함수
	- 헤더 파일로 `#inclue <stdlib.h>`를 선언 후 사용 가능.
	- `int system(const char* command);`
	- Shell 명령어를 실행하기 위한 함수
	- `command`에 지정된 명령어를 실행하며, 명령어가 끝난 후 반환. 리턴된 값은 호출이 실패한다면 127, 다른 에러가 있다면 -1, 그렇지 않으면 명령어의 리턴 코드가 반환.

* 연결리스트 구조
![linkedlist.jpg](./linkedlist.jpg)

* argc, argv 등의 개념
	- argc는 실행 파일과 함께 입력한 인자들의 개수를 카운트
	- argv는 문자열로 저장된 인자의 주솟값을 배열형태로 저장. 공백 단위로 끊어서 인덱스에 하나씩 저장

## 실제 수행 항목

### 1. 헤더 파일 작성

- 구조체 및 필요 함수 선언

### 2. 메인 파일 작성

- 쉘의 기본 구조 작성(첫 입력과 기본 출력)
- linkedlist 구조 구현 중

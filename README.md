# ATmega128 PlatformIO 메모

## 요약
- PlatformIO CLI가 PATH에 없어서 전체 경로로 `pio` 실행 필요.
- 미러 DNS 문제로 toolchain 다운로드 실패 -> 수동 설치 후 성공.
- 보드/프로그래머 미연결 상태에서는 업로드 실패가 정상.

## 반영된 변경
- `upload_command`에 `sysenv.USERPROFILE` 사용해 PC마다 경로 차이 해결.
- `platformio/toolchain-atmelavr@^3.70300.220127`로 toolchain 버전 고정.

## 명령어
- 빌드
  - PowerShell: & "C:\Users\<User>\.platformio\penv\Scripts\pio.exe" run
- 업로드
  - PowerShell: & "C:\Users\<User>\.platformio\penv\Scripts\pio.exe" run -t upload

## 참고
- 여러 PC를 쓰면 각 PC에 `C:\Users\<User>\.platformio\penv\Scripts`를 PATH에 추가하거나 전체 경로로 실행.
- 업로드 시 프로그래머/보드가 연결되어 있어야 함. 미연결 시 `avrdude`에서 USB 장치를 찾지 못하는 오류가 발생.

## 관찰된 오류
- `MissingPackageManifestError`: 불완전한 toolchain 폴더로 발생, 재설치 및 버전 고정으로 해결.
- 업로드 오류: 프로그래머 미연결 상태에서 `avrdude`가 USB 장치를 찾지 못함.

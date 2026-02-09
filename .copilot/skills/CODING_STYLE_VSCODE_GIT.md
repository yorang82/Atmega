## 11. VS Code 환경 설정 (PC 간 호환성)

### 11.1 문제점

`.vscode/tasks.json`, `.vscode/settings.json`, `.vscode/launch.json` 등의 파일은 **절대 경로**를 포함하기 때문에 PC마다 다른 경로로 인해 호환성 문제가 발생합니다.

**예시 (문제가 되는 코드):**
```json
{
    "command": "& \"C:\\ST\\STM32CubeIDE_1.18.0\\STM32CubeIDE\\headless-build.bat\" -data \"E:\\workspace\""
}
```

### 11.2 해결 방법

**1) 환경 변수 사용**

절대 경로 대신 환경 변수를 사용합니다:

```json
{
    "command": "& \"${env:STM32_CUBE_IDE}\\headless-build.bat\" -data \"${env:STM32_WORKSPACE}\""
}
```

**2) 환경 변수 설정 방법 (Windows)**

PowerShell에서 시스템 환경 변수 설정:
```powershell
[System.Environment]::SetEnvironmentVariable('STM32_CUBE_IDE', 'C:\ST\STM32CubeIDE_1.18.0\STM32CubeIDE', 'User')
[System.Environment]::SetEnvironmentVariable('STM32_WORKSPACE', 'E:\workspace', 'User')
```

또는 GUI로 설정:
- Windows 설정 → 시스템 → 정보 → 고급 시스템 설정 → 환경 변수
- 사용자 변수에 추가:
  - `STM32_CUBE_IDE` = `C:\ST\STM32CubeIDE_1.18.0\STM32CubeIDE`
  - `STM32_WORKSPACE` = `E:\workspace`

**3) .gitignore 설정**

개인별 환경 설정 파일은 Git에서 제외합니다:

```gitignore
# VS Code (workspace 설정은 유지, 개인별 환경 설정은 제외)
.vscode/*.log
.vscode/tasks.json
.vscode/settings.json
.vscode/launch.json
```

### 11.3 새 PC에서 프로젝트 설정

1. **환경 변수 설정**: 각 PC에 맞는 경로로 환경 변수 설정
2. **tasks.json 복사**: `.vscode/tasks.json.example` 같은 템플릿을 제공하거나, README에 설정 방법 기록
3. **환경 변수 확인**: VS Code 터미널에서 `echo $env:STM32_CUBE_IDE` 로 확인

### 11.4 주의사항

- ⚡ `.vscode` 폴더의 개인 설정 파일은 **절대 Git에 커밋하지 않습니다**
- ⚡ 프로젝트 공유 시 README에 필요한 환경 변수 목록과 설정 방법을 명시합니다
- ⚡ 새로운 채팅에서는 "루시, tasks.json 설정해줘"라고 요청하면 자동으로 환경 변수 기반 설정이 적용됩니다

---

## 12. VS Code IntelliSense 설정

### 12.1 Ctrl+클릭 함수 이동이 안 될 때

**증상:**
- Ctrl+클릭으로 함수 정의로 이동이 안 됨
- 코드 자동완성이 작동하지 않음
- 함수 선언 찾기 기능이 동작하지 않음

**해결 방법:**

#### 1단계: IntelliSense 활성화 확인

`.vscode/settings.json` 파일 확인:

```json
{
    "C_Cpp.intelliSenseEngine": "default",
    "C_Cpp.errorSquiggles": "enabled",
    "cmake.configureOnOpen": false
}
```

❌ **잘못된 설정 (IntelliSense 비활성화됨):**
```json
{
    "C_Cpp.intelliSenseEngine": "disabled",
    "C_Cpp.errorSquiggles": "Disabled"
}
```

#### 2단계: 컴파일러 경로 확인

`.vscode/c_cpp_properties.json` 파일의 `compilerPath` 확인:

```json
{
    "configurations": [
        {
            "name": "Win32",
            "compilerPath": "C:/ST/STM32CubeIDE_X.XX.X/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.XX.X.relX.win32_X.X.XXX.XXXXXXXXXXXXXX/tools/bin/arm-none-eabi-gcc.exe",
            ...
        }
    ]
}
```

**컴파일러 경로 찾는 방법:**
```powershell
# STM32CubeIDE 버전 확인
Get-ChildItem "C:\ST" -Directory

# GNU tools 플러그인 폴더 찾기
Get-ChildItem "C:\ST\STM32CubeIDE_X.XX.X\STM32CubeIDE\plugins" -Directory | Where-Object { $_.Name -like "*gnu-tools*" }
```

#### 3단계: VS Code 창 다시 로드

- **Ctrl+Shift+P** → `Developer: Reload Window`
- IntelliSense가 색인 생성할 때까지 대기 (우측 하단 상태바에서 진행 상황 확인)

### 12.2 CMake 경고 제거

STM32 프로젝트는 CMake를 사용하지 않으므로, `.vscode/settings.json`에 추가:

```json
{
    "cmake.configureOnOpen": false
}
```

### 12.3 Git 설정

`.gitignore`에 PC별 설정 파일 추가:

```gitignore
# VS Code (PC별 환경 설정은 제외)
.vscode/*.log
.vscode/tasks.json
.vscode/settings.json
.vscode/launch.json
.vscode/c_cpp_properties.json
```

**이유:**
- 각 PC마다 STM32CubeIDE 설치 경로가 다름
- IntelliSense 설정이 개인 환경에 따라 다를 수 있음

### 12.4 새 PC 설정 체크리스트

1. ✅ STM32CubeIDE 설치 경로 확인
2. ✅ `.vscode/c_cpp_properties.json`의 `compilerPath` 수정
3. ✅ `.vscode/settings.json`에서 IntelliSense 활성화
4. ✅ VS Code 창 다시 로드 (`Developer: Reload Window`)
5. ✅ Ctrl+클릭으로 함수 이동 동작 확인

---
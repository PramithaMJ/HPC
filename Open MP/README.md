# OpenMP

![1747814683450](images/README/1747814683450.png)

### **What is OpenMP?**

OpenMP is an **API (Application Programming Interface)**. That means it's a set of tools and commands programmers can use in their code.

* It helps write **parallel programs** — programs that can run multiple parts at the same time.
* It works with **shared memory** systems (like most modern multi-core CPUs).
* It supports **C, C++**, and **Fortran** programming languages.
* It runs on **many types of computer hardware**, making it portable.

# **OpenMP Has 3 Main Parts:**

1. **Compiler Directives**
   Commands (e.g., `#pragma omp parallel`) you put in your source code to tell the compiler where to use threads.
2. **Runtime Library Routines**
   Built-in functions (like `omp_get_thread_num()`) that give you control during the program run.
3. **Environment Variables**
   System settings (like `OMP_NUM_THREADS`) that influence how the program behaves when using OpenMP.

### ** “OpenMP” Stand For?**

* **Short version**: Open Multi-Processing
* **Long version**: A **standard for multiprocessing**, created by a **collaboration** of hardware and software companies, government, and academia.

### **What OpenMP Is NOT:**

It’s **not perfect**, and the programmer still has responsibilities:

* Different vendors may implement it **differently**.
* It doesn't guarantee **optimal performance**.
* It won’t check for:
  * **Data races**
  * **Deadlocks**
  * **Invalid code**
* It doesn’t automatically handle **file I/O synchronization**. You must manage it yourself.

### **Goals of OpenMP:**


| Goal                | Description                                                       |
| ------------------- | ----------------------------------------------------------------- |
| **Standardization** | A common way to write parallel code across many platforms.        |
| **Lean and Mean**   | Originally designed to use just a few simple directives (3–4).   |
| **Ease of Use**     | Allows gradual (incremental) parallelization of existing code.    |
|  **Portability**    | Works with C/C++ and Fortran on many OSes (Unix, Linux, Windows). |

> Note: The "lean and mean" goal is less accurate today, as newer versions are more complex.

### **Brief History of OpenMP:**

* **Early 1990s**: Vendors made their own versions of parallel Fortran using directives.
* **1994**: ANSI tried to create a standard (ANSI X3H5), but it failed due to declining interest.
* **Mid-late 1990s**: Shared-memory machines became more popular again.
* **1997**: OpenMP specification began, led by the **OpenMP Architecture Review Board (ARB)**.

#### Contributors:

* Intel, IBM, HP, Sun, Compaq, KAI, DOE, and more.
* Software partners like ANSYS, Fluent, NAG.
* Compiler vendors like PGI, Absoft.

### **OpenMP Version Release History:**


| Version | Language | Release Date |
| ------- | -------- | ------------ |
| 1.0     | Fortran  | Oct 1997     |
| 1.0     | C/C++    | Oct 1998     |
| 1.1     | Fortran  | Nov 1999     |
| 2.0     | Fortran  | Nov 2000     |
| 2.0     | C/C++    | Mar 2002     |
| 2.5     | Combined | May 2005     |
| 3.0     | Combined | May 2008     |
| 3.1     | Combined | Jul 2011     |
| 4.0     | Combined | Jul 2013     |
| 5.0     | Combined | Nov 2018     |
| 5.1     | Combined | Nov 2020     |
| 5.2     | Combined | Nov 2021     |

>  **Note**: The tutorial you’re studying refers mainly to **OpenMP 3.1**, not 4.x or 5.x.

### **Resources **

* [OpenMP Website](https://www.openmp.org/)
* [Wikipedia: OpenMP](https://en.wikipedia.org/wiki/OpenMP)
* Tutorial from **Lawrence Livermore National Laboratory (LLNL)**

## Summary

* **OpenMP** is a standard way to write **multi-threaded programs** on shared-memory systems using C, C++, or Fortran.
* It’s made up of:
  1. **Directives**
  2. **Library Functions**
  3. **Environment Variables**
* **Programmers** must ensure correctness (e.g., avoid data races and I/O conflicts).
* It’s **portable**, **relatively easy to learn**, and **evolves with time** (current stable version: 5.2).
* **In this repo tutorial uses version 3.1**, so examples will match that standard.


## **OpenMP Programming Model**

### **1**. Memory Model: **Shared Memory**

**OpenMP** is **built **for **shared **memory **machines****,** where **all **threads **see **the **same **memory******.** That **means:**

* One copy of the data is **shared** among threads.
* **Can** be **implemented** on **both:**
  * **UMA** (**Uniform** Memory **Access):** equal **memory** access **speed** for **all** CPUs.
  * **NUMA** (**Non-** Uniform **Memory** Access): **access** time **depends** on **memory** location **relative** to **the** CPU.

### **2.** **Execution** Model: **Thread-** Based **Parallelism**

* **Threads** are small **tasks** that **run** in **parallel.**
* **OpenMP** uses **threads** to **do** all **its** parallel **work.**
* **Threads** live **inside** a **single **process**** — **they** can't **exist** on **their** own.

#### facts:

* **Usually,** the **number** of **threads =** number **of** processor **cores.**
* **But** this **is** **up** to the **programmer **or **runtime******, not **automatic.**

### **3.** Explicit Parallelism (**Not **Automatic)****

You (the programmer) must:

* **Manually **tell**** **OpenMP** where **to** run **code** in **parallel.**
* **Do** this **using** **compiler **directives**** (e.g., `#pragma omp parallel`).

> **This** gives **you** **full **control**** **over** what **runs** in **parallel.**

### **4.** **Fork-** Join Model (Very **Important)**

**This** is **the** **core** model **of** how **OpenMP** runs **your** code.

#### **Process:**

1. **Start**: **Your** program **starts** with  **one **thread**** – **the ****master****.**
2. **Fork** **:** When **it** hits **a ****parallel **region******,** the **master** **creates** a **team** **of** threads.
3. **Work** **:** All **threads** in **the** team **run** the **parallel** code **together.**
4. **Join** **:** After **the** parallel region, all **threads** finish **and **disappear****, **leaving** only **the** master thread.

> This **pattern** repeats **throughout** the program.

### **5.** **Compiler** Directive- **Based **Programming****

**You** control **parallelism **using **special **keywords****, **called **compiler **directives**:

* In **C/** C++: `#pragma omp ...`
* In Fortran: `!$omp ...`

**These** tell the **compiler **which **parts** of **the** code should **run **in **parallel****.**

### **6.** **Nested **Parallelism****

**You** can **put** a **parallel** region **inside **another**** **parallel** region.

* **Some** compilers **may** **not** support this fully.
* **Useful** for **complex** or **hierarchical** tasks.

### **7.** **Dynamic **Threads****

**OpenMP** can **adjust** the **number** of **threads** **during **runtime**** (**if** allowed **by** your **system).**

* **Helps** use **system **resources **more **efficiently****
* **Also** **not **guaranteed**** **to** be **supported** everywhere.

### **8.** Parallel **I/** O: **You’re**on Your **Own**

**OpenMP** **does** NOT **manage** input/**output** (e.g., **reading/** writing **files)** between **threads.**

* **If** multiple **threads** write **to** the **same** file **at** the **same** time, **you** **must** handle **the **synchronization**** **yourself.**
* **Otherwise,** you may **get **corrupted or **mixed-**up **data****.**

### **9.** Execution + Memory = **SPMD **Model****

**OpenMP** uses **the** **Single** Program, **Multiple** Data (**SPMD)** **model:**

* **All** threads **run** **the** same **program **code****.
* **But** they **may:**
  * **Work **on **different **data****.
  * **Take** **different **paths**** **through** the **code.**

### **10.** **Thread** Memory **View:** Relaxed **Consistency**

* **All **threads **share **memory**** , but **each** thread **can** also **have** **private** temporary **copies** **of** variables.
* **These** **may** not **automatically **sync**** **with** shared **memory.**

#### **When** you **need** all **threads** to **see** the **same** value:

must **manually** sync **memory** **using:**

* `flush` **directive,** or
* **Rely** on **compiler** to **handle** sync **when** a **thread** **exits **a **parallel **region******.**

### **11.** **What** You **Need** to **Do** as **a** Programmer

**When** writing **OpenMP** programs, **you** must:


| **Task**                           | **What** It **Means**                                                         |
| ---------------------------------- | ------------------------------------------------------------------------------- |
| ****Start** threads**             | **Use**a**directive**like`#pragma omp parallel`                                 |
| ****Count** threads**             | **Use**`omp_get_num_threads()`                                                  |
| ****Identify** threads**          | **Use**`omp_get_thread_num()`                                                   |
| ****Join** threads**              | **After** a **parallel** region **ends,** threads **join** automatically |
| ****Synchronize** threads**       | **Use** barriers, **critical** sections, **etc.**                           |
| ****Maintain** data** consistency | **Ensure** data **updates** are **visible** to **all** threads           |
| ****Handle** race** conditions    | **Be** aware **of** data conflicts, deadlocks, **etc.**                    |

## **Summary**

* OpenMP **uses** a **thread-**based**, ****explicit****,** **fork-**join **model****.**
* You **control **threads **using **directives****,**not** automatic tools.
* **Memory **is **shared**, **but** you **must **manage consistency **and **I/**O****.**
* **It** follows **the ****SPMD **model******,** where **all** threads **run** the **same** code **but** can **take** different **actions.**
* Programmers **are** responsible **for** correctness, **efficiency,** and **safe** parallel execution.

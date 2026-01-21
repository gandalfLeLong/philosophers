# philosophers

In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes.

---

### 💡 Key Features
* **Multithreading:** Each philosopher is represented by a thread, running a simulation of eating, sleeping, and thinking.
* **Mutexes:** Implements mutual exclusion to protect shared resources (forks) and prevent data races.
* **Synchronization:** Precise monitoring to detect if a philosopher dies of starvation within milliseconds.
* **Optimization:** Compiled with high-performance flags (`-flto`, `-O3`) and tested for synchronization issues using ThreadSanitizer.

---

### 🛠️ Compilation & Usage

The project includes a **Makefile** to manage the compilation of the `philo` binary.

| Rule | Description |
| :--- | :--- |
| `make` | Compiles the `philo` executable with aggressive optimizations. |
| `make debug` | Compiles with `-fsanitize=thread` to detect data races. |
| `make clean` | Removes the `objects/` directory. |
| `make fclean` | Removes objects and the `philo` binary. |
| `make re` | Recompiles the entire project. |

**To run the simulation:**
Pass the following arguments: `number_of_philosophers` `time_to_die` `time_to_eat` `time_to_sleep` `[optional: number_of_times_each_philosopher_must_eat]`

```bash
./philo 5 800 200 200

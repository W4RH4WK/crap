% Techniques
% Alex Hirsch

# Planning

## Meet the Problem

![](images/problem-1.svg)

## Analysis

- Understand the problem
- Relation to similar problems
- Existing solutions

## Dissecting

- Break a big problem into smaller problems
- Often pieces share similarities
- `goto Analysis`

---

![](images/problem-2.svg)

---

![](images/problem-3.svg)

## Problem Description

- Document, fully describing the problem
- Mentions every detail discovered
- Result of your analysis process

## Solution

- Start with the big picture
  - Block diagrams
  - UML
- Define modules
  - Purpose
  - What to cover
- Define module interaction
  - Interfaces between modules

---

- Go through each module
  - Think critically about its tasks
  - How can it be realised?
  - What problems could emerge?
  - How does data flow through this module?

## Solution Specification

- Document, fully describing the solution
- Needs to communicate the big picture
- May contain lots of details
- Consider it a guide for implementing

## Managing Time

- Split the implementation work into small, manageable tasks
- Think critically about relationships between tasks
  - Does feature A depend on feature B?
- Consider which resources are needed for each task
  - Do we need special equipment?
  - Who will work on this?
- *Maybe* add time estimates to tasks
  - Avoid unless you really have to

## Gantt Chart

![Src: teamgantt.com](images/gantt_chart.png)

## Iterating

- Problem changes over time
- Solution has shortcomings
- Resource situation changes

Core idea behind *agile* software development.

---

![](images/overcome.jpg)

---

- Update problem description
- Make changes to your solution specification
- Update your management plan accordingly
- Flexibility is paramount

This commonly decides between success and failure.

---

Stay away from *scrum* and alike, it's probably a big scam.

# Software Architecture

## Modules

- Each module should fulfil a specific purpose
  - *Separation of Concerns*
- Modules interact with each other to achieve greater tasks
  - Interface of a module
  - Module dependencies
  - Level of abstraction (high-level vs. low-level)

## Interfaces

- Multiple modules need to work together
- Smaller interfaces provide more flexibility
  - *Loose coupling*
- Need to be clearly defined
- Should be free from implementation details

## Abstractions

If things get too complicated, adding another layer may help.

---

![](images/abstraction-1.svg)

---

![](images/abstraction-2.svg)

---

- Sometimes introduces more code
  - Ensure trade-off is worth it
- Details become less obvious
  - The devil is in the detail
- Think in layers
  - How far am I from the lowest level?

> You aren't gonna need it!

## Cross Layer Interaction

![](images/cross_layer_interaction.svg)

# Implementation

## Types

- Types are documentation
- Use meaningful types (e.g. `bool`)
- Use structs / class to group data that belongs together (e.g. `User`)

## Functions

```c
double square(double n);

bool is_prime(int n);

int sum(const int *data, int size);

double clamp(double value, double lower, double upper);

double xfb(int a, int b, double pre); // 🤔
```

---

- Signatures are documentation
- `const` pointers signal input, non-`const` pointers signal output
- If signature gets too complex
  - Use a struct for parameters / return value
  - Split function, would be too complicated anyway

---

- Which global state does the function touch?
- Observe the call-graph
  - Which parts of the program call this function?
  - Which functions are called by this function?
- Which layer of abstraction are we on?

---

- Number of local variables should not exceed 7
- How long is the function?
- How complicated is the control-flow?

## Variables

- Again, use the correct type
- Meaningful name, don't abbreviate (e.g. `wnd` vs. `window`)
- `const` by default
- Always initialise
- Limit their scope
  - Manually
  - Utilise variable declaration inside `for` (and `if` since C++17)

---

```c
int main(void)
{
    int number1, number2, number3,
        difference1, difference2, difference3,
        larger_numbers, smallest_difference,
        secret_number, winner;
    // …
}
```

Bad

---

```c
int main(void)
{
    srand(time(NULL));
    int secret = rand() % 100;

    while (true) {
        int guess1 = get_guess();
        int guess2 = get_guess();
        int guess3 = get_guess();

        // …
    }
}
```

Good

---

```c++
const auto direction = physx::PxVec3(inputDir.x, 0.f, inputDir.y)
const auto strength = 2000.0 * timeDelta;

entity->addTorque(strength * direction, physx::PxForceMode::eIMPULSE);

// …
```

Bad

---

```c++
{
    const auto direction = physx::PxVec3(inputDir.x, 0.f, inputDir.y)
    const auto strength = 2000.0 * timeDelta;

    entity->addTorque(strength * direction, physx::PxForceMode::eIMPULSE);
}

// …
```

Good

## Control-Flow

- Linearize as much as possible
- Limit nesting depth
- Avoid complex `break` / `continue` constructs
- Avoid conditionals / loops inside `switch`
- Use empty lines to separate blocks that belong together

Use additional functions (or macros) if things get too complex.

---

```c
void foo(void)
{
    if (first()) {
        // …
        if (second()) {
            // …
            if (third()) {
                // …
            }
        }
    }
}
```

Bad

---

```c
void foo(void)
{
    if (!first())
        return;

    // …

    if (!second())
        return;

    // …

    if (!third())
        return;

    // …
}
```

Good

## Comments

- Comments should explain **why** something is happening
- Code should specify **what** is happening
- Do not introduce comments where none are necessary
- Consider overview comments at the beginning of files
  - Keep them free of implementation details

Avoid comments that need to be kept in sync with other parts of the code.

---

```c++
double Engine::updateTimestamp()
{
    const auto now = Clock::now();

    auto delta = now - m_timestamp;
    m_timestamp = now;

    // cap delta to 100 milliseconds
    delta = std::min<Clock::duration>(delta, 50ms);

    // …
}
```

Bad

---

```c++
double Engine::updateTimestamp()
{
    const auto now = Clock::now();

    auto delta = now - m_timestamp;
    m_timestamp = now;

    // Large time deltas can cause issues with physics simulations. Capping it
    // here affects the whole simulation (not just physics) equally.
    delta = std::min<Clock::duration>(delta, 50ms);

    // …
}
```

Good

## Classes

- Put together what belongs together (data and functions)
  - Adhere to separation of concerns
- Clearly communicate invariants
- Interfaces much bigger than your regular functions
  - Make sure this trade-off is worth it!
  - Limit the number of public methods (and variables)
- Think critically about the lifetime (and ownership) of instances
- Try to minimize mutability of held data
- Auto-generate getters / equality / hash / … **at compile-time**

---

```haskell
data Person = Person { firstName :: String
                     , lastName  :: String
                     , age       :: Int
                     }
  deriving (Eq, Ord, Show, Read)

main = print $ Person "John" "Doe" 28
```

```
Person {firstName = "John", lastName = "Doe", age = 28}
```

## Cognitive Load

Bottom line: keep it to a minimum.

# Testing

## V-Model

![Src: geeksforgeeks.org](images/v_model.png)

## How to write useful tests?

- Start with unit testing
- Focus on black-box testing
- Focus on testing complex logic
- Test error cases (negative tests)
- Observe test coverage
- Add integration tests

Consider test driven development (TDD).

---

- Use a testing framework
- Integrate it into the build system
- Make it easy to write and run tests!
  - See Go or Rust for instance

---

```
make         # builds the project

make test    # runs all unit tests

scripts/run_integration_tests
```

---

![Test Runner (Src: microsoft.com)](images/test_runner.png))

## Continuous Integration

- Let services (Jenkins, GitLab CI, …) build and test your code
- Reject merge-requests which break tests
- View this as a form of quality assurance

---

![Jobs](images/jenkins-1.png)

---

![Configurations](images/jenkins-2.png)

---

![Build History](images/jenkins-3.png)

---

![Pipelines](images/gitlab_ci.png)

---

![Pull Requests](images/github_ci.png)

# Profiling

## About Profiling

- Not that important right now
- Always measure!
  - What to measure, what to optimise?
  - Are the values you measure meaningful?!
  - Relate multiple measurements over time
- Can be applied to multiple layers
  - Micro-benchmarks (similar to unit tests)
  - Overall benchmark
- Profile **release** builds!

---

![Benchmarks](images/benchmarks.png)

---

![Profiling](images/profiling.svg)

---

- Correctly present plots
  - Labelled axes
  - Grid lines
  - Print data points (no need to connect them)
  - Put some reference there
  - Use a suitable scale
  - Consider logarithmic axes

# Debugging

## How to debug

- Investigate the symptoms
- Use your brain!
  - Are they expected?
  - What could cause these symptoms?
- Formulate hypothesis
  - Try to **dis-**prove it!
  - Narrow the scope of it
  - Immediately test assumptions

## Dealing with Segfaults

- Use your brain!
  - Disprove hypothesis
  - Use different configurations (optimisation level)
- Are there compiler warnings?
- Does Valgrind show issues?
- Run in GDB, observe stack trace
  - Examine local variables / parameters
  - Investigate other stack frames `up` / `down`
  - Symptom ≠ cause
- Investigate lifetime and ownership of related objects

⟶ Bug description

---

- Create a dedicated test
  - Will fail at the moment
- Solve the issue
  - Test should now be successful
  - Did I break anything?
- Commit your fix (+ test)

# Collaborating

## Working in Teams

- Select a *project officer*
  - A developer, not a manager
  - Someone with authority
  - Maintains the big picture
  - Can make decisions
  - Who's decisions are respected by the team

Imagine an orchestra without its conductor.

---

- Don't be on the offensive (all the time)
  - Be respectful of other people's code
  - Ensure your code is working fine and is well tested
  - Ensure your code is well documented
  - Add assertions (defensive programming)

---

- Propose changes to other people's code via pull-requests
  - Use scientific reasoning when arguing
  - Accept their decision either way
- Consider doing code-reviews
  - Improves the overall code-quality
  - You learn a lot from it
  - The code-base becomes more similar

## Joining a new Team

- Start by doing the tasks no one else wants to do
  - This way you get accepted more easily by a group
  - Show that you can pull your weight
  - Show that you have something meaningful to contribute
  - Don't step on other people's toes

---

- Understand the big picture
- Understand the modules
- Understand their interactions
- Add **useful** documentation to the code-base
- Sometimes tasks are marked as *good for beginners*
  - Pick one up and try to solve it
  - Ask the corresponding maintainers, but respect their time

---

Stick with people you feel comfortable with.

## Management vs. Developers

- Management
  - Necessary to some extend
  - Knows very little about technical stuff
  - Mostly concerned with business decisions
- Developers
  - Good technical knowledge
  - Wants to build stuff

---

- Managers should not interfere with developer's work
  - Keep meetings to a minimum and keep groups small
  - Ensure developers have the resources they need
- Developers should not replace managers (if present)
  - Managers typically have more to worry about than you think
  - Respect manager's decisions

## Hierarchies

- Very similar to abstractions
  - The higher you go, the more details get lost
  - Remember, the devil is in the detail!
- Strive for shallow, hierarchies (2–3 layers often enough)

## Development Teams (Squads)

- Homogeneous vs. heterogenous
- Task / feature oriented
- Will touch many modules of the code-base over time
- Work may conflict with other squads'

## Concept of Maintainers

- Associated with specific modules (e.g. database)
- Squads coordinate with the corresponding maintainers
- Maintainers are regular developers

## Devops

Sounds good, doesn't work.

## Open Source Community

- Welcoming
- Developers highly occupied
- Better to submit code than just opening issues
  - Talk about bigger changes / features beforehand
- Learn about their workflow before contributing
- Keep bug descriptions objective and detailed
- Respect their work and decisions
- Be thankful for their effort

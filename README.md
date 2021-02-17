# Welcome to MyStudy!
## Category
- [UnrealEngine](/UnrealEngine/)
- [C,C++](/C,C++/)
- [C#](/C%23/)
- [Unity](/Unity/)
- [English](/English/)
- [Regex](/Regex)
- [OS Architecture](/OS_Architecture)
- [Misc](/Misc)
- [Github](/Github/)

## UML diagrams

You can render UML diagrams using [Mermaid](https://mermaidjs.github.io/). For example, this will produce a sequence diagram:

```mermaid
sequenceDiagram
Alice ->> Bob: Hello Bob, how are you?
Bob-->>John: How about you John?
Bob--x Alice: I am good thanks!
Bob-x John: I am good thanks!
Note right of John: Bob thinks a long<br/>long time, so long<br/>that the text does<br/>not fit on a row.

Bob-->Alice: Checking with John...
Alice->John: Yes... John, how are you?
```

And this will produce a flow chart:

```mermaid
graph LR
A[Square Rect] -- Link text --> B((Circle))
A --> C(Round Rect)
B --> D{Rhombus}
C --> D
```
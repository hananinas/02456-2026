# Quiz Check — Week 2 (FNN / Autodiff / Nanograd)

*Date: 2026-09-09*

## Status: 3/10 solid, 3/10 partially right, 4/10 missed

## Progress Tracker

| Q | Topic | Status | Revisit? |
|---|-------|--------|----------|
| 1 | mul gradient = sibling's value (a.grad=5, b.grad=3) | Partial | Yes |
| 2 | add gradient = 1, `[(self,1.0),(other,1.0)]` | Correct | No |
| 3 | backward twice accumulates (`self.grad += bp`) | Missed | **Yes** |
| 4 | finite difference: (f(3+da)−f(3))/da ≈ 5.0 | Missed | **Yes** |
| 5 | activation Var holds transformed value t, grad separate | Partial | Yes |
| 6 | σ' = σ(1−σ), tanh' = 1−tanh², ranges (0,1) / (−1,1) | Correct | No |
| 7 | identity = returns value unchanged; used for regression output | Partial | Yes |
| 8 | forward: node = bias + Σ w·x, then activation | Correct | No |
| 9 | weights[i][j]: i=inputs, j=output nodes; Vars for backprop | Missed | **Yes** |
| 10 | identity: grad passes through; mul: scaled by sibling value | Missed | **Yes** |

## My Answers (as given)

1. "df/da and df/db are there gradient" — too vague; needed: df/da = b, df/db = a, so a.grad=5, b.grad=3
2. "(self, 1.0), (other, 1.0) as gradient is 1" ✓
3. *skipped*
4. Answered with backprop line instead of finite-difference formula
5. "value is squished between 0 and 1... differentiated version returned" — right idea, wrong details (tanh is −1..1)
6. "sigmoid(x)(1−sigmoid(x)) and 1−tanh*tanh" ✓
7. "returns the gradient of the input with regards to itself 1" — confused value with derivative
8. "bias and weight times its value" ✓ (say: sum over ALL inputs)
9. "layer and hidden layers" — wrong; i = inputs, j = output nodes
10. "check gradient by differentiating using chain rule" — too vague

## Key Facts To Remember

- **mul**: local grad = *other operand's value* → f=a*b, a=3,b=5 → a.grad=5, b.grad=3
- **add**: local grad = 1, always
- **identity**: f(x)=x, local grad 1, gradient passes through unchanged (used on output layer so regression gets raw values)
- **relu**: returns x if x>0 else 0, local grad 1 or 0
- **sigmoid** = 1/(1+exp(−x)), range (0,1), σ' = σ(1−σ)
- **tanh** = (exp(x)−exp(−x))/(exp(x)+exp(−x)) = 2·sigmoid(2x)−1, range (−1,1), tanh' = 1−tanh²
- **exp** = e^x (math.exp) — the *opposite* of log, not the same
- **Exercise c**: running backward() again ADDS again (self.grad += bp) → a.grad 5→10
- **Exercise e**: finite difference `(f(a+da) − f(a))/da`, da=1e-10 → ≈5.0, matches backward()'s grad
- **New activation pattern**: `Var(t, lambda: [(self, t*(1−t))])` — value = transformed number, lambda = derivative for backprop
- **Exercise g forward**: `node = self.bias[j]` then `node += weights[i][j] * single_input[i]`, then `act_fn(node)` → σ(Σw·x + b)
- **weights[i][j]**: i indexes inputs (n_in), j indexes output nodes (n_out). Weights are Var objects so gradients ∂loss/∂w can be computed → that's what training learns

## Answers (checked & corrected)

<details>
<summary>Q1</summary>
df/da = b, df/db = a. With a=3, b=5: a.grad = 5, b.grad = 3.
</details>

<details>
<summary>Q3</summary>
Gradient accumulates: a.grad goes 5 → 10 on second run. Caused by `self.grad += bp`.
</details>

<details>
<summary>Q4</summary>
(f(a+da) − f(a)) / da with da = 1e-10 → prints ≈ 5.0 for f = a*b, matching backward().
</details>

<details>
<summary>Q5</summary>
New node value must be the transformed number t (e.g. t = σ(x) or tanh(x)), NOT self.v — that would make identity. The lambda holds the derivative, used only during backprop.
</details>

<details>
<summary>Q7</summary>
Identity returns the VALUE unchanged (f(x)=x); its derivative is 1. Used on output layer for regression: raw value needed, no squashing.
</details>

<details>
<summary>Q9</summary>
i runs over inputs (rows, n_in); j runs over output nodes (columns, n_out). Weights must be Vars so backward() can build the graph through them and compute ∂loss/∂w — these are the learnable parameters.
</details>

<details>
<summary>Q10</summary>
Through identity: gradient passes through unchanged (1 × upstream). Through multiplication: scaled by the other operand's value (e.g. 5×10=50 vs 1×10=10).
</details>

## Next Quiz Focus

1. Accumulation on repeated backward (Q3)
2. Finite difference formula (Q4)
3. weights[i][j] index meaning (Q9)
4. Gradient flow through identity vs mul (Q10)
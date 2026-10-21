# GnuCash BPMN product requirements and review

## Basis and decision

This specification is for **modeling existing GnuCash workflows**, not proposing a new application. Its authority is the team's `Value Propositions Canvas.pdf` (business requirements on p. 3, process inventory on p. 4, personas on pp. 5–6, value proposition on p. 8, and business model on p. 9), the ten draft `.bpmn` files, and the GnuCash source tree in `../gnucash`. The canvas prioritizes a **personal user**; accountant and small business owner are secondary personas. The value is structured, balanced accounting, account monitoring, budgeting, scheduled transactions, reconciliation, reports, and optional small business A/R and A/P.

**Recommendation: four top-level BPMN diagrams.** They show four outcomes instead of ten menu features. Reuse existing diagrams as detail or collapsed subprocesses; do not delete the originals. Model investment management as an optional future diagram because it appears only as a product in the value proposition, not in BR-01–06 or the p. 4 process inventory. If the course requires only core personal finance, submit diagrams 1–3 and show diagram 4 as the small business extension.

| Final diagram | Purpose / outcome | Drafts to reuse | Canvas trace |
|---|---|---|---|
| 1. Establish and maintain financial records | Valid chart of accounts and balanced transactions, whether entered, imported, or generated on a schedule | 01, 02, 08, 09 | BR-01, BR-02, BR-04; steps A–C, F |
| 2. Reconcile a bank account | Completed statement period with zero unexplained difference | 03, plus correction/import call activities from 1 | BR-05; step D |
| 3. Plan and evaluate finances | Budget and current financial view, with reviewed variance and report | 06, 07 | BR-03, BR-04; steps E, G |
| 4. Manage small business receivables and payables | Posted invoice/bill and correctly allocated full or partial payment | 04, 05 | BR-06; step H |

### Audit of the ten drafts

| Draft | Assessment and correction for redraw |
|---|---|
| 01 Chart of accounts | Good setup subprocess. Include parent account, account type, commodity/currency, and opening balance as an **opening balance transaction**, not an account property. Existing account path can simply reuse it. |
| 02 Transaction entry | Core process. Keep entry and correction paths. Do not imply a transaction can only be saved after manually checking debit = credit: model GnuCash's imbalance handling as a visible exception requiring review. `Void` is not the same as a reversing journal entry; label them separately. Deletion needs an explicit user decision. |
| 03 Reconciliation | Essential. Add statement date and ending balance before matching, a zero-difference gateway, and return to matching after corrections. Replace “lock account” with “mark selected splits reconciled”; it is not a permanent account lock. Bank and user pools are appropriate only if message receipt is really depicted. |
| 04 Invoicing A/R | Appropriate secondary workflow. Add an explicit **post invoice** action before it creates receivable; calculating and saving a draft does not post it. Record/allocate a payment to the customer and invoice; full versus partial is an outcome, not a different accounting mechanism. Do not assume GnuCash automatically emails an invoice. |
| 05 Bills A/P | Appropriate secondary workflow. Add **post bill** before payable exists. Record payment to vendor and allocate it to a bill. A payment recorded in GnuCash is not proof the bank transferred funds or vendor received them; external transfer/receipt requires a separate manual or external actor step. |
| 06 Budgeting | Appropriate, but “all budget lines filled” is not a required gate; users may budget selected accounts. “Corrective action” is a human business decision outside GnuCash. Use a report to compare budget with actual transactions. |
| 07 Financial reports | Appropriate. Connect generation and optional export/sharing in one process or subprocess. Do not promise every report can export in every listed format; use “supported save/print/export option.” Report accuracy depends on the recorded data and selected options. |
| 08 Data import | Appropriate entry variant. Duplicate detection is a **candidate match for user review**, not an automatic proof of duplication. Include format/read failure, account mapping, review of each candidate, and cancellation. Avoid a gateway loop that can cycle forever without advancing to the next item. |
| 09 Scheduled transactions | Appropriate supporting subprocess. A reminder, automatic creation, and user-confirmed creation are different configured outcomes. Include the due date, review/edit/skip/defer choices, and prevent double posting. Do not assert that the scheduler independently runs in the background while the desktop app is closed. |
| 10 Investment portfolio | Plausible GnuCash capability, but outside the explicit business process and BR list. Keep as optional specialist appendix if needed. Buying/selling/dividends have different accounts and transaction splits; the current one-size form would need more detail. |

The drafts mostly use unnamed pools or no lanes, and some put several disconnected starts in one file. That can be valid for separate processes, but it weakens the presentation of one end-to-end outcome. For each final diagram, define one main start and meaningful end, use named lanes for **User** and **GnuCash**, and use a separate pool only for a genuinely external participant. Sequence flows stay inside a pool; message flows cross pools. Label every exclusive gateway's outgoing paths and ensure every loop has a route to completion or cancellation. Use user tasks for human work and service/script tasks only for automatic software behavior. Represent reuse of detailed entry, import, or payment workflows with a call activity or collapsed subprocess.

## Requirement 1 — Establish and maintain financial records

**Goal.** A personal user or accountant has an account hierarchy and records income, expense, transfer, asset, and liability events in double-entry form. This is the main process; import and scheduling are alternatives to manual entry, not separate business outcomes.

**Trigger:** new book/account need, new financial event, incoming supported transaction file, or due scheduled transaction. **Preconditions:** a GnuCash book is open; required account currencies/commodities are known; for import, a supported file is available; for scheduled entry, a schedule exists. **End:** posted/recorded transaction visible in the appropriate register, or an explicit cancel/skip with no transaction created.

**Lanes:** User (personal user or accountant); GnuCash. Optional external Bank/File Source pool only for providing an import file; no claim of automatic bank sync.

**Main path to model:**

1. User identifies the financial event and checks whether the needed account exists.
2. If absent, user creates an account under the appropriate asset/liability/equity/income/expense parent, chooses type and commodity, and supplies an opening balance through an opening balance transaction if necessary. GnuCash stores the account.
3. Exclusive gateway **entry source?** Manual / Import / Scheduled. This is one choice for the current event, not three parallel executions.
4. **Manual:** user selects a register, enters date, description, amount and counter-account or splits. GnuCash calculates the total of splits and shows any imbalance. User corrects account or amount and confirms entry.
5. **Import:** user selects a supported file and destination account; GnuCash parses it and proposes matches/categories; user checks account mapping and each proposed new/matched/duplicate item, corrects or skips as needed, then confirms import. Only accepted items become transactions.
6. **Scheduled:** at application review of due schedules, GnuCash presents due occurrences according to the schedule's configured reminder/auto-create behavior. User confirms, edits, postpones or skips where review is configured. Confirmed occurrence creates a transaction once and advances the occurrence schedule.
7. GnuCash saves the transaction and updates account balances; user reviews it in the register.

**Exceptions:** missing/wrong account → return to account selection; malformed/unsupported import file → explain error and stop import without posting; uncertain duplicate/match → user decides; unbalanced splits → user corrects or explicitly handles GnuCash's imbalance account, never silently label the record balanced; schedule skipped/deferred → no current transaction; invalid save → remain in editing path. If an existing transaction is wrong, model a linked correction subprocess: edit, void, reverse with a separate transaction, or delete after confirmation as appropriate, then recheck balances.

**Data objects:** chart of accounts, transaction date/description, splits, account/commodity, import file and match decisions, schedule/frequency/next occurrence. **Acceptance scenarios:** income entered against bank and income accounts; transfer between two asset accounts; imported candidate identified as already recorded and skipped; due scheduled expense postponed without a duplicate entry; split totals visibly checked; opening balance affects a transaction rather than account metadata.

**Copy-ready BPMN prompt:** “Create one BPMN 2.0 diagram titled ‘Establish and Maintain Financial Records in GnuCash’. Pools: user/GnuCash lanes, optional external file source. Start from a financial event; check/create chart-of-account entry; use an exclusive gateway for manual, file import, or due scheduled transaction; show each as a collapsed subprocess with the steps and exceptions specified above; merge only after a transaction is confirmed; end at recorded balanced transaction or explicit cancellation/skip. Label gateway conditions. Use no unsupported automatic bank sync.”

## Requirement 2 — Reconcile a bank account

**Goal.** Confirm that GnuCash's account activity for a statement period agrees with the bank statement and identify missing/incorrect items.

**Trigger:** bank statement is available. **Preconditions:** account and transactions exist; statement date and ending balance are known. **End:** reconciliation committed with zero difference, or paused/cancelled with discrepancy unresolved.

**Lanes/pools:** User and GnuCash lanes; Bank as a separate pool only to provide the statement.

**Main path:** user selects the bank account, statement date and ending balance; GnuCash displays eligible uncleared items and the reconciliation difference; user checks only items present on statement; gateway **difference = 0?** If yes, user finishes reconciliation and GnuCash marks selected splits reconciled. If no, user compares statement and ledger to find missing, duplicate, wrong amount/date, or wrongly selected item; user changes selections or invokes transaction entry/correction/import from requirement 1; GnuCash recalculates; loop back to zero-difference gateway. Allow pause/cancel without falsely marking the period complete.

**Data:** statement, statement date/ending balance, selected splits, computed difference. **Acceptance:** zero difference finishes; one missing bank fee is entered and rechecked; wrong selection is unchecked; unresolved difference cannot take the successful end. Do not depict permanent locking of the account.

**Copy-ready BPMN prompt:** “Draw one BPMN 2.0 collaboration ‘Reconcile Bank Account in GnuCash’. The Bank sends a statement to the User; User and GnuCash are separate lanes in the GnuCash process. Enter statement date and ending balance, mark matching transactions, recalculate difference, loop on mismatch through investigate/correct/import, finish only at zero difference, and show pause/cancel as a distinct end. Finishing marks selected splits reconciled, not the entire account locked.”

## Requirement 3 — Plan and evaluate finances

**Goal.** Let the personal user or small business owner set budget amounts, compare actual results, and inspect/share a financial report. This joins planning and monitoring into one recurring decision cycle.

**Trigger:** new planning period or review date. **Preconditions:** relevant accounts exist; meaningful actual comparison requires recorded transactions. **End:** budget saved and financial situation reviewed; optional report saved/printed/shared by the user.

**Lanes:** User and GnuCash; optional recipient as an external pool only if report delivery is in scope.

**Main path:** user chooses budget period and selected accounts, enters amounts for intended periods, reviews and saves; during the period user opens budget-versus-actual and/or financial report/graph, selects report type, dates and available options; GnuCash calculates from the book; user checks the result; gateway **data/options appropriate?** If no, adjust filters or correct ledger data through requirement 1 and regenerate. If yes, user assesses variances and may revise the plan or take an offline action. User may use a supported save/print/export action. Model a timer or separate review trigger for later cycles rather than making GnuCash autonomously enforce financial decisions.

**Data:** budget periods/accounts/amounts, actual ledger transactions, report type/options/date range, report output. **Acceptance:** partial budget is allowed; actual expense above budget shows variance; changing report period recalculates; the process can finish without exporting; sharing happens only after a user action.

**Copy-ready BPMN prompt:** “Draw ‘Plan and Evaluate Finances in GnuCash’ in BPMN 2.0 with User and GnuCash lanes. Start at a new budget or review period. Show selected-account budget creation, later budget-versus-actual comparison, financial report configuration and generation, a quality-check loop for wrong data/options, human variance review, optional revise-budget and optional save/print/share. Do not require every account to have a budget, and show human corrective decisions outside automatic GnuCash tasks.”

## Requirement 4 — Manage small business receivables and payables

**Goal.** A small business owner/accountant tracks customer receivables and vendor payables, including partial settlement. This is an extension, not a prerequisite for personal-use diagrams.

**Trigger:** customer sale to invoice or vendor bill received; later, payment received or payment to vendor recorded. **Preconditions:** business book, customer/vendor, appropriate A/R or A/P and income/expense accounts exist. **End:** posted invoice or bill remains open with correct outstanding balance, or is fully paid after payment allocation.

**Lanes/pools:** User and GnuCash lanes; Customer and Vendor pools only when showing actual delivery/receipt messages. Keep A/R and A/P as two mutually exclusive branches or two collapsed subprocesses in the same top-level diagram.

**A/R path:** user chooses customer and creates invoice items, dates, amounts, applicable tax terms; GnuCash calculates total; user checks and explicitly **posts invoice** to A/R; user delivers/prints invoice outside the posting task if needed. Later user records a customer payment to the chosen asset account and allocates it to the customer/invoice; GnuCash reduces outstanding A/R. Gateway **remaining balance = 0?** Full → paid; partial → open with remainder. If invoice needs correction before posting, edit draft; if after posting, use the supported unpost/correct workflow with appropriate caution.

**A/P path:** user checks vendor's bill, enters items, due date, amounts and taxes; GnuCash calculates total; user checks and explicitly **posts bill** to A/P; at payment time user records the vendor payment from a chosen asset account and allocates it to the bill; GnuCash reduces outstanding A/P. Gateway **remaining balance = 0?** Full → paid; partial → open with remainder. Recording a payment in GnuCash is distinct from sending money through a bank.

**Exceptions:** missing customer/vendor or account → create/select before posting; mismatched amount/tax → correct draft; payment unallocated or exceeds intended bill/invoice → user reviews allocation; external payment failure → do not claim settlement merely from initiating transfer. **Data:** customer/vendor, invoice/bill lines, dates, tax, A/R or A/P account, payment amount/account, allocation and outstanding balance. **Acceptance:** draft creates no receivable/payable; posting does; partial payment leaves correct balance; full payment closes balance; A/R and A/P never share the same invoice/bill record.

**Copy-ready BPMN prompt:** “Create one BPMN 2.0 diagram ‘Manage Small Business Receivables and Payables in GnuCash’. Use a gateway for customer invoice versus vendor bill and collapsed A/R and A/P subprocesses. In each: create and review draft, explicitly post to A/R or A/P, later record and allocate a payment, calculate outstanding balance, and end paid or partially open. Distinguish recording payment from real-world transfer/delivery. Show User and GnuCash lanes and external pools only for actual messages.”

## Submission checks

1. Every top-level diagram has a purpose, clear start, successful and cancelled/paused end, named actor lanes, data objects, and labeled gateway conditions.
2. Every system task corresponds to an existing GnuCash behavior; real-world bank transfer, email delivery, and business corrective action remain user/external tasks.
3. A record is considered balanced because its splits sum correctly; an invoice or bill affects A/R or A/P only after posting; reconciliation succeeds only at zero difference.
4. BPMN XML opens in the team's viewer, all sequence-flow references resolve, every branch can terminate, and message flows connect separate pools only.
5. Trace each diagram to the table above; keep original ten files as supporting detailed subprocess drafts or appendices.

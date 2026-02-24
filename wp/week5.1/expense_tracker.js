/*
Expense Tracker with total calculation
add expense, title, amount, category
dispplay list expenses
delete expenses
show total expenses
highlight expenses greater than 5000
use expense class
maintain array of expenses
validation of amount (only positive)
*/

// ============================================================
//  EXPENSE TRACKER — Pure JavaScript (no HTML file needed)
//  Run with:  node expense-tracker.js
//  Or open in a browser via a <script> tag (it self-renders)
// ============================================================

class Expense {
  constructor(id, title, amount, category) {
    this.id = id;
    this.title = title;
    this.amount = amount;
    this.category = category;
    this.date = new Date().toLocaleDateString("en-IN", {
      day: "2-digit", month: "short", year: "numeric"
    });
  }
}

class ExpenseTracker {
  #expenses = [];
  #nextId = 1;
  #HIGHLIGHT_THRESHOLD = 5000;

  // ── CRUD ─────────────────────────────────────────────────
  addExpense(title, amount, category) {
    const parsed = parseFloat(amount);
    if (!title || !title.trim())        throw new Error("Title is required.");
    if (isNaN(parsed) || parsed <= 0)   throw new Error("Amount must be a positive number.");
    if (!category || !category.trim())  throw new Error("Category is required.");

    const expense = new Expense(this.#nextId++, title.trim(), parsed, category.trim());
    this.#expenses.push(expense);
    return expense;
  }

  deleteExpense(id) {
    const idx = this.#expenses.findIndex(e => e.id === id);
    if (idx === -1) throw new Error(`No expense found with ID ${id}.`);
    const [removed] = this.#expenses.splice(idx, 1);
    return removed;
  }

  getExpenses()    { return [...this.#expenses]; }
  getTotal()       { return this.#expenses.reduce((s, e) => s + e.amount, 0); }
  isHighlighted(e) { return e.amount > this.#HIGHLIGHT_THRESHOLD; }
}

// ── BROWSER RENDERER ────────────────────────────────────────
(function boot() {
  if (typeof document === "undefined") {
    console.log("Run in a browser. Open this .js file via an HTML page.");
    return;
  }

  // ── Inject HTML skeleton ──────────────────────────────────
  document.documentElement.lang = "en";
  document.head.innerHTML = `
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width,initial-scale=1"/>
    <title>Expense Tracker</title>
    <link rel="preconnect" href="https://fonts.googleapis.com"/>
    <link href="https://fonts.googleapis.com/css2?family=Playfair+Display:wght@700&family=DM+Mono:wght@400;500&display=swap" rel="stylesheet"/>
  `;

  // ── CSS ───────────────────────────────────────────────────
  const style = document.createElement("style");
  style.textContent = `
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    :root {
      --bg:        #0d0d0d;
      --surface:   #161616;
      --border:    #2a2a2a;
      --accent:    #e8c84b;
      --danger:    #ff4d4d;
      --highlight: #1a1200;
      --hl-border: #e8c84b;
      --text:      #e8e8e8;
      --muted:     #666;
      --font-head: 'Playfair Display', serif;
      --font-mono: 'DM Mono', monospace;
    }

    body {
      background: var(--bg);
      color: var(--text);
      font-family: var(--font-mono);
      min-height: 100vh;
      padding: 2rem 1rem 4rem;
    }

    header {
      text-align: center;
      margin-bottom: 2.5rem;
    }
    header h1 {
      font-family: var(--font-head);
      font-size: clamp(2rem, 5vw, 3.2rem);
      color: var(--accent);
      letter-spacing: -1px;
    }
    header p {
      color: var(--muted);
      font-size: .8rem;
      margin-top: .4rem;
    }

    .wrapper {
      max-width: 760px;
      margin: 0 auto;
      display: grid;
      gap: 1.8rem;
    }

    /* ── FORM ── */
    .form-card {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 4px;
      padding: 1.5rem 1.8rem;
    }
    .form-card h2 {
      font-family: var(--font-head);
      font-size: 1.1rem;
      color: var(--accent);
      margin-bottom: 1.2rem;
      border-bottom: 1px solid var(--border);
      padding-bottom: .6rem;
    }
    .form-grid {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: .8rem 1rem;
    }
    .form-grid .span2 { grid-column: 1 / -1; }
    label { font-size: .72rem; color: var(--muted); display: block; margin-bottom: .3rem; }
    input, select {
      width: 100%;
      background: #1e1e1e;
      border: 1px solid var(--border);
      border-radius: 3px;
      color: var(--text);
      font-family: var(--font-mono);
      font-size: .85rem;
      padding: .55rem .75rem;
      outline: none;
      transition: border-color .2s;
    }
    input:focus, select:focus { border-color: var(--accent); }
    select option { background: #1e1e1e; }

    .btn {
      cursor: pointer;
      font-family: var(--font-mono);
      font-size: .82rem;
      font-weight: 500;
      letter-spacing: .05em;
      border: none;
      border-radius: 3px;
      padding: .6rem 1.4rem;
      transition: opacity .15s, transform .1s;
    }
    .btn:active { transform: scale(.97); }
    .btn-add {
      background: var(--accent);
      color: #000;
      width: 100%;
      margin-top: .4rem;
      padding: .75rem;
    }
    .btn-add:hover { opacity: .88; }
    .btn-del {
      background: transparent;
      color: var(--danger);
      border: 1px solid var(--danger);
      padding: .3rem .7rem;
      font-size: .75rem;
    }
    .btn-del:hover { background: var(--danger); color: #fff; }

    /* ── TOAST ── */
    #toast {
      position: fixed;
      bottom: 1.5rem;
      left: 50%;
      transform: translateX(-50%) translateY(80px);
      background: #222;
      color: var(--text);
      font-family: var(--font-mono);
      font-size: .8rem;
      padding: .6rem 1.4rem;
      border-radius: 30px;
      border: 1px solid var(--border);
      transition: transform .3s ease, opacity .3s ease;
      opacity: 0;
      pointer-events: none;
      z-index: 999;
    }
    #toast.show { transform: translateX(-50%) translateY(0); opacity: 1; }
    #toast.error { border-color: var(--danger); color: var(--danger); }

    /* ── TOTAL BANNER ── */
    .total-banner {
      display: flex;
      justify-content: space-between;
      align-items: center;
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 4px;
      padding: 1rem 1.5rem;
    }
    .total-banner .label { font-size: .72rem; color: var(--muted); }
    .total-banner .amount {
      font-family: var(--font-head);
      font-size: 1.8rem;
      color: var(--accent);
    }
    .total-banner .count { font-size: .78rem; color: var(--muted); }

    /* ── LIST ── */
    .list-card {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 4px;
      padding: 1.5rem 1.8rem;
    }
    .list-card h2 {
      font-family: var(--font-head);
      font-size: 1.1rem;
      color: var(--accent);
      margin-bottom: 1.2rem;
      border-bottom: 1px solid var(--border);
      padding-bottom: .6rem;
    }

    #expense-list { list-style: none; display: grid; gap: .6rem; }

    .expense-item {
      display: flex;
      align-items: center;
      gap: 1rem;
      padding: .75rem 1rem;
      border: 1px solid var(--border);
      border-radius: 3px;
      background: #111;
      animation: slideIn .25s ease;
      transition: border-color .2s;
    }
    .expense-item.highlighted {
      background: var(--highlight);
      border-color: var(--hl-border);
    }
    @keyframes slideIn {
      from { opacity: 0; transform: translateY(-8px); }
      to   { opacity: 1; transform: translateY(0); }
    }

    .exp-id   { color: var(--muted); font-size: .68rem; min-width: 26px; }
    .exp-info { flex: 1; }
    .exp-title { font-size: .88rem; }
    .exp-meta  { font-size: .7rem; color: var(--muted); margin-top: .15rem; }
    .exp-badge {
      font-size: .65rem;
      background: #2a2a2a;
      color: var(--accent);
      border-radius: 30px;
      padding: .15rem .55rem;
    }
    .expense-item.highlighted .exp-badge { background: #2d2500; }
    .exp-amount {
      font-family: var(--font-head);
      font-size: 1.05rem;
      color: var(--text);
      white-space: nowrap;
    }
    .expense-item.highlighted .exp-amount { color: var(--accent); }
    .hl-tag {
      font-size: .62rem;
      color: var(--accent);
      background: #2d2500;
      border: 1px solid #4a3800;
      border-radius: 2px;
      padding: .1rem .4rem;
    }

    .empty-state {
      text-align: center;
      color: var(--muted);
      font-size: .82rem;
      padding: 2rem 0;
    }

    @media (max-width: 500px) {
      .form-grid { grid-template-columns: 1fr; }
      .form-grid .span2 { grid-column: 1; }
    }
  `;
  document.head.appendChild(style);

  // ── HTML ─────────────────────────────────────────────────
  document.body.innerHTML = `
    <header>
      <h1>Expense Tracker</h1>
      <p>Amounts &gt; ₹5,000 are highlighted</p>
    </header>

    <div class="wrapper">
      <div class="total-banner">
        <div>
          <div class="label">TOTAL EXPENSES</div>
          <div class="amount" id="total">₹0.00</div>
        </div>
        <div class="count" id="count">0 entries</div>
      </div>

      <div class="form-card">
        <h2>Add Expense</h2>
        <div class="form-grid">
          <div>
            <label for="title">TITLE</label>
            <input id="title" type="text" placeholder="e.g. Laptop, Groceries"/>
          </div>
          <div>
            <label for="amount">AMOUNT (₹)</label>
            <input id="amount" type="number" min="0.01" step="0.01" placeholder="e.g. 4500"/>
          </div>
          <div class="span2">
            <label for="category">CATEGORY</label>
            <select id="category">
              <option value="">— select —</option>
              <option>Food & Dining</option>
              <option>Transport</option>
              <option>Shopping</option>
              <option>Entertainment</option>
              <option>Health</option>
              <option>Utilities</option>
              <option>Education</option>
              <option>Other</option>
            </select>
          </div>
          <div class="span2">
            <button class="btn btn-add" id="add-btn">+ ADD EXPENSE</button>
          </div>
        </div>
      </div>

      <div class="list-card">
        <h2>Expense List</h2>
        <ul id="expense-list"><li class="empty-state">No expenses yet. Add one above.</li></ul>
      </div>
    </div>

    <div id="toast"></div>
  `;

  const tracker = new ExpenseTracker();

  const listEl  = document.getElementById("expense-list");
  const totalEl = document.getElementById("total");
  const countEl = document.getElementById("count");
  const toast   = document.getElementById("toast");
  let toastTimer;

  function fmt(n) {
    return "₹" + n.toLocaleString("en-IN", { minimumFractionDigits: 2, maximumFractionDigits: 2 });
  }

  function showToast(msg, isError = false) {
    clearTimeout(toastTimer);
    toast.textContent = msg;
    toast.className = "show" + (isError ? " error" : "");
    toastTimer = setTimeout(() => { toast.className = ""; }, 2800);
  }

  function render() {
    const expenses = tracker.getExpenses();
    const total    = tracker.getTotal();

    totalEl.textContent = fmt(total);
    countEl.textContent = `${expenses.length} entr${expenses.length === 1 ? "y" : "ies"}`;

    if (!expenses.length) {
      listEl.innerHTML = `<li class="empty-state">No expenses yet. Add one above.</li>`;
      return;
    }

    listEl.innerHTML = expenses.map(e => {
      const hl = tracker.isHighlighted(e);
      return `
        <li class="expense-item${hl ? " highlighted" : ""}" data-id="${e.id}">
          <span class="exp-id">#${e.id}</span>
          <div class="exp-info">
            <div class="exp-title">${e.title} <span class="exp-badge">${e.category}</span></div>
            <div class="exp-meta">${e.date}</div>
          </div>
          ${hl ? `<span class="hl-tag">HIGH</span>` : ""}
          <span class="exp-amount">${fmt(e.amount)}</span>
          <button class="btn btn-del" data-id="${e.id}">✕</button>
        </li>`;
    }).join("");
  }

  document.getElementById("add-btn").addEventListener("click", () => {
    const title    = document.getElementById("title").value;
    const amount   = document.getElementById("amount").value;
    const category = document.getElementById("category").value;

    try {
      const exp = tracker.addExpense(title, amount, category);
      document.getElementById("title").value    = "";
      document.getElementById("amount").value   = "";
      document.getElementById("category").value = "";
      render();
      showToast(`"${exp.title}" added — ${fmt(exp.amount)}`);
    } catch (err) {
      showToast(err.message, true);
    }
  });

  listEl.addEventListener("click", e => {
    const btn = e.target.closest(".btn-del");
    if (!btn) return;
    const id = parseInt(btn.dataset.id);
    try {
      const removed = tracker.deleteExpense(id);
      render();
      showToast(`"${removed.title}" deleted.`);
    } catch (err) {
      showToast(err.message, true);
    }
  });

  // Allow Enter key on inputs
  ["title","amount","category"].forEach(id => {
    document.getElementById(id).addEventListener("keydown", ev => {
      if (ev.key === "Enter") document.getElementById("add-btn").click();
    });
  });

  render();
})();
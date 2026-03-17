const words = {
  easy: [
    {w:"CAT",   c:"Animals",  h:"Common house pet"},
    {w:"DOG",   c:"Animals",  h:"Man's best friend"},
    {w:"FOX",   c:"Animals",  h:"Sly orange forest creature"},
    {w:"BEAR",  c:"Animals",  h:"Loves honey and salmon"},
    {w:"FROG",  c:"Animals",  h:"Jumps and croaks"},
    {w:"DUCK",  c:"Animals",  h:"Quack quack!"},
    {w:"LION",  c:"Animals",  h:"King of the jungle"},
    {w:"WOLF",  c:"Animals",  h:"Howls at the moon"},
    {w:"APPLE", c:"Fruits",   h:"Keeps the doctor away"},
    {w:"GRAPE", c:"Fruits",   h:"Grows in bunches on vines"},
    {w:"LEMON", c:"Fruits",   h:"Makes you pucker up"},
    {w:"MANGO", c:"Fruits",   h:"Tropical yellow fruit"},
    {w:"PEACH", c:"Fruits",   h:"Soft, fuzzy summer fruit"},
    {w:"PIZZA", c:"Food",     h:"Italy's greatest export"},
    {w:"CAKE",  c:"Food",     h:"Birthday table star"},
    {w:"SOUP",  c:"Food",     h:"Warm liquid meal"},
    {w:"RICE",  c:"Food",     h:"Staple Asian grain"},
    {w:"BREAD", c:"Food",     h:"Made from flour and yeast"},
    {w:"RAIN",  c:"Nature",   h:"Falls from clouds"},
    {w:"SNOW",  c:"Nature",   h:"White winter flakes"},
    {w:"TREE",  c:"Nature",   h:"Tall wooden plant"},
    {w:"MOON",  c:"Nature",   h:"Earth's natural satellite"},
    {w:"STAR",  c:"Nature",   h:"Twinkles in the night sky"},
    {w:"GOLF",  c:"Sports",   h:"Hit a tiny ball into a hole"},
    {w:"CHESS", c:"Sports",   h:"Strategy board game"},
  ],
  medium: [
    {w:"MONKEY",  c:"Animals",    h:"Swings from jungle trees"},
    {w:"PARROT",  c:"Animals",    h:"Colorful talking tropical bird"},
    {w:"RABBIT",  c:"Animals",    h:"Hops and has long ears"},
    {w:"TURTLE",  c:"Animals",    h:"Carries its home on its back"},
    {w:"GORILLA", c:"Animals",    h:"Largest primate on Earth"},
    {w:"FALCON",  c:"Animals",    h:"Fastest bird in the world"},
    {w:"LOBSTER", c:"Animals",    h:"Red clawed seafood delicacy"},
    {w:"BURRITO", c:"Food",       h:"Wrapped Mexican meal"},
    {w:"PANCAKE", c:"Food",       h:"Flat breakfast cake"},
    {w:"CHICKEN", c:"Food",       h:"Most popular poultry"},
    {w:"POPCORN", c:"Food",       h:"Movie night snack"},
    {w:"BROWNIE", c:"Food",       h:"Chocolate fudge square"},
    {w:"WAFFLE",  c:"Food",       h:"Grid-patterned breakfast treat"},
    {w:"VOLCANO", c:"Nature",     h:"Mountain of fire"},
    {w:"TORNADO", c:"Nature",     h:"Spinning wind funnel"},
    {w:"RAINBOW", c:"Nature",     h:"Colorful arc after rain"},
    {w:"GLACIER", c:"Nature",     h:"Massive slow-moving ice river"},
    {w:"LAPTOP",  c:"Technology", h:"Portable personal computer"},
    {w:"BROWSER", c:"Technology", h:"You surf the web with this"},
    {w:"NETWORK", c:"Technology", h:"Connected computers sharing data"},
    {w:"CRICKET", c:"Sports",     h:"Bat and ball sport"},
    {w:"TENNIS",  c:"Sports",     h:"Racket sport across a net"},
    {w:"LIBRARY", c:"Places",     h:"Quiet home of many books"},
    {w:"SURGEON", c:"Jobs",       h:"Operates on patients in hospital"},
    {w:"CAPTAIN", c:"Jobs",       h:"Commands a ship or team"},
  ],
  hard: [
    {w:"HIPPOPOTAMUS",   c:"Animals",    h:"Large semiaquatic African mammal"},
    {w:"CHIMPANZEE",     c:"Animals",    h:"Our closest primate cousin"},
    {w:"CROCODILE",      c:"Animals",    h:"Ancient apex reptile predator"},
    {w:"SALAMANDER",     c:"Animals",    h:"Fire-legend amphibian"},
    {w:"PHOTOSYNTHESIS", c:"Science",    h:"How plants convert sunlight to food"},
    {w:"METAMORPHOSIS",  c:"Science",    h:"Caterpillar-to-butterfly transformation"},
    {w:"ELECTRICITY",    c:"Science",    h:"Flow of electric charge that powers homes"},
    {w:"BIODIVERSITY",   c:"Science",    h:"Variety of life on Earth"},
    {w:"CRYPTOGRAPHY",   c:"Technology", h:"Science of secret codes and ciphers"},
    {w:"PROGRAMMING",    c:"Technology", h:"Writing instructions for computers"},
    {w:"CYBERSECURITY",  c:"Technology", h:"Protecting digital systems from attack"},
    {w:"IMAGINATION",    c:"Concepts",   h:"The ability to form mental images"},
    {w:"TRANSFORMATION", c:"Concepts",   h:"A complete and dramatic change"},
    {w:"DETERMINATION",  c:"Concepts",   h:"Firmness of purpose, never giving up"},
    {w:"PERSEVERANCE",   c:"Concepts",   h:"Continuing despite obstacles"},
    {w:"EXTRAORDINARY",  c:"Concepts",   h:"Going beyond what is ordinary"},
    {w:"SWITZERLAND",    c:"Countries",  h:"Famous for chocolate, watches and Alps"},
    {w:"MADAGASCAR",     c:"Countries",  h:"Large island nation with unique lemurs"},
    {w:"ARCHAEOLOGY",    c:"Academic",   h:"Study of ancient civilizations"},
    {w:"MATHEMATICS",    c:"Academic",   h:"Study of numbers, patterns and proofs"},
    {w:"PHILOSOPHY",     c:"Academic",   h:"Love of wisdom and deep thinking"},
    {w:"ENCYCLOPEDIA",   c:"Objects",    h:"Comprehensive reference book"},
    {w:"KALEIDOSCOPE",   c:"Objects",    h:"Rotating colourful pattern toy"},
    {w:"THUNDERSTORM",   c:"Nature",     h:"Storm with lightning and heavy rain"},
    {w:"CONSTELLATION",  c:"Space",      h:"Named pattern of stars in the night sky"},
  ]
};

const modes = {
  normal:    {name:"Normal Mode",    emoji:"🎮", lives:6, time:0,  color:"#4ECDC4", shadow:"#2ba39c", desc:"Classic hangman! Guess the word before the hangman is fully drawn. You have 6 chances."},
  timetrial: {name:"Time Trial",     emoji:"⏱️", lives:6, time:30, color:"#FF6B6B", shadow:"#c0392b", desc:"30 seconds to guess as many words as possible. Each correct word scores 1 point!"},
  hardcore:  {name:"Hardcore Mode",  emoji:"💀", lives:1, time:0,  color:"#A78BFA", shadow:"#6d28d9", desc:"One wrong letter = instant Game Over. Only the brave dare attempt Hardcore Mode."},
};

const diffs = {
  easy:   {name:"Easy",   emoji:"😊", color:"#4ADE80"},
  medium: {name:"Medium", emoji:"😐", color:"#FBBF24"},
  hard:   {name:"Hard",   emoji:"😰", color:"#F87171"},
};

let g = {
  mode: null, diff: null,
  word: "", category: "", hint: "",
  guessed: new Set(),
  wrong: 0, gameOver: false,
  score: 0, timeLeft: 0, timer: null
};

const $ = id => document.getElementById(id);

function showScreen(id) {
  document.querySelectorAll(".screen").forEach(s => s.classList.remove("active"));
  $(id).classList.add("active");

  const isGame = id === "s-game";
  $("keyboard-section").classList.toggle("hidden", !isGame);
  $("lives-bar").classList.toggle("hidden", !isGame);
  $("wrong-letters").classList.toggle("hidden", !isGame);
  $("hardcore-badge").classList.toggle("hidden", !(isGame && g.mode === "hardcore"));
  $("tt-bar").classList.toggle("hidden", !(isGame && g.mode === "timetrial"));
  $("tagline").classList.toggle("hidden", isGame);

  if (!isGame) {
    for (let i = 0; i <= 6; i++) {
      const el = $("p" + i);
      if (el) el.style.opacity = 0;
    }
  }
}

function selectMode(mode) {
  g.mode = mode;
  showScreen("s-diff");
}

function selectDiff(diff) {
  g.diff = diff;
  const m = modes[g.mode];
  const d = diffs[diff];

  $("desc-card").style.setProperty("--mc", m.color);
  $("desc-icon").textContent = m.emoji;
  $("desc-title").textContent = m.name;
  $("desc-text").textContent = m.desc;
  $("btn-start").style.cssText = `--mc:${m.color};--ms:${m.shadow}`;
  $("desc-pills").innerHTML = `
    <span class="pill" style="background:${d.color};color:#1a1a1a">${d.emoji} ${d.name}</span>
    ${m.time ? `<span class="pill" style="background:#FFE66D;color:#1a1a1a">⏱️ ${m.time}s</span>` : ""}
    <span class="pill" style="background:#E0E7FF;color:#1a1a1a">💔 ${m.lives === 1 ? "1 life" : m.lives + " lives"}</span>
  `;
  showScreen("s-desc");
}

function pickWord() {
  const pool = words[g.diff];
  return pool[Math.floor(Math.random() * pool.length)];
}

function initGame() {
  clearInterval(g.timer);
  const picked = pickWord();
  g.word = picked.w;
  g.category = picked.c;
  g.hint = picked.h;
  g.guessed = new Set();
  g.wrong = 0;
  g.gameOver = false;
  g.score = 0;
  g.timeLeft = modes[g.mode].time;

  $("cat-name").textContent = g.category;
  $("cat-hint").textContent = "💡 " + g.hint;
  showScreen("s-game");
  renderWord();
  renderKeyboard();
  renderHangman();
  renderLives();
  $("wrong-letters").textContent = "";

  if (g.mode === "timetrial") {
    $("tt-timer").textContent = "⏱️ " + g.timeLeft + "s";
    $("tt-timer").className = "tt-timer";
    $("tt-score").textContent = "⭐ Score: 0";
    g.timer = setInterval(tick, 1000);
  }
}

function tick() {
  g.timeLeft--;
  const el = $("tt-timer");
  el.textContent = "⏱️ " + g.timeLeft + "s";
  el.className = "tt-timer" + (g.timeLeft <= 10 ? " danger" : "");
  if (g.timeLeft <= 0) {
    clearInterval(g.timer);
    g.gameOver = true;
    showResult(false, true);
  }
}

function renderHangman() {
  for (let i = 0; i < 6; i++) $("p" + i).style.opacity = i < g.wrong ? 1 : 0;
  $("p6").style.opacity = g.wrong >= 6 ? 1 : 0;
}

function renderLives() {
  const max = modes[g.mode].lives;
  $("lives-bar").innerHTML = Array.from({length: max}, (_, i) =>
    `<span class="heart${i >= max - g.wrong ? "" : " lost"}">❤️</span>`
  ).join("");
}

function renderWord() {
  $("word-display").innerHTML = g.word.split("").map(ch => {
    if (ch === " ") return `<div class="slot space"><div class="letter"> </div><div class="dash"></div></div>`;
    const rev = g.guessed.has(ch);
    return `<div class="slot${rev ? " revealed" : ""}">
      <div class="letter${rev ? " pop" : ""}">${rev ? ch : ""}</div>
      <div class="dash"></div>
    </div>`;
  }).join("");
}

function renderKeyboard() {
  const rows = ["QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"];
  $("keyboard").innerHTML = rows.map(row =>
    `<div class="kb-row">${row.split("").map(l => {
      const used = g.guessed.has(l);
      const cls  = used ? (g.word.includes(l) ? " correct" : " wrong") : "";
      return `<button class="kb-btn${cls}" ${used || g.gameOver ? "disabled" : ""} onclick="guess('${l}')">${l}</button>`;
    }).join("")}</div>`
  ).join("");
}

function guess(letter) {
  if (g.gameOver || g.guessed.has(letter)) return;
  g.guessed.add(letter);
  const inWord = g.word.includes(letter);
  if (!inWord) g.wrong++;

  renderWord();
  renderKeyboard();
  renderHangman();
  renderLives();
  $("wrong-letters").textContent = [...g.guessed].filter(l => !g.word.includes(l)).map(l => l).join("  ") || "";
  if ($("wrong-letters").textContent) $("wrong-letters").textContent = "✗ " + $("wrong-letters").textContent;

  const won = g.word.split("").filter(c => c !== " ").every(c => g.guessed.has(c));

  if (won) {
    if (g.mode === "timetrial") {
      g.score++;
      $("tt-score").textContent = "⭐ Score: " + g.score;
      flashScore();
      const next = pickWord();
      g.word = next.w; g.category = next.c; g.hint = next.h;
      g.guessed = new Set();
      g.wrong = 0;
      $("cat-name").textContent = g.category;
      $("cat-hint").textContent = "💡 " + g.hint;
      renderWord(); renderKeyboard(); renderHangman(); renderLives();
      $("wrong-letters").textContent = "";
    } else {
      g.gameOver = true;
      showResult(true, false);
    }
    return;
  }

  const maxLives = modes[g.mode].lives;
  if ((g.mode === "hardcore" && !inWord) || g.wrong >= maxLives) {
    clearInterval(g.timer);
    g.wrong = maxLives;
    g.gameOver = true;
    renderHangman();
    renderLives();
    setTimeout(() => showResult(false, false), 400);
  }
}

function flashScore() {
  const el = $("tt-flash");
  el.classList.remove("hidden", "pop");
  void el.offsetWidth;
  el.classList.add("pop");
  setTimeout(() => el.classList.add("hidden"), 900);
}

function showResult(won, timeout) {
  $("res-emoji").textContent = timeout ? "⏰" : won ? "🎉" : "💀";
  $("res-title").textContent = timeout ? "Time's Up!" : won ? "You Win!" : "Game Over!";
  $("res-title").className   = "res-title " + (timeout ? "timeout" : won ? "win" : "lose");
  $("res-word").innerHTML    = "The word was: <strong>" + g.word + "</strong>";

  const scoreEl = $("res-score");
  if (g.mode === "timetrial") {
    scoreEl.textContent = "🌟 Score: " + g.score + (g.score === 1 ? " word" : " words");
    scoreEl.classList.remove("hidden");
  } else {
    scoreEl.classList.add("hidden");
  }

  $("result").classList.remove("hidden");
}

function playAgain() {
  $("result").classList.add("hidden");
  initGame();
}

function goHome() {
  clearInterval(g.timer);
  $("result").classList.add("hidden");
  showScreen("s-home");
}

document.addEventListener("keydown", e => {
  const l = e.key.toUpperCase();
  if (/^[A-Z]$/.test(l) && $("s-game").classList.contains("active")) guess(l);
});

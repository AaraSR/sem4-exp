/* ─── DOM EVENTS LAB — dom.js ───────────────────────────────── */

// ─── UTILITY: LOG ENTRY ──────────────────────────────────────
const tagColors = {
  click:     { bg: 'rgba(0,245,255,0.15)',   color: '#00f5ff' },
  focus:     { bg: 'rgba(170,255,0,0.15)',   color: '#aaff00' },
  blur:      { bg: 'rgba(107,107,138,0.2)',  color: '#6b6b8a' },
  keydown:   { bg: 'rgba(170,255,0,0.15)',   color: '#aaff00' },
  keyup:     { bg: 'rgba(170,255,0,0.08)',   color: '#88cc00' },
  keypress:  { bg: 'rgba(170,255,0,0.08)',   color: '#aaff00' },
  submit:    { bg: 'rgba(0,245,255,0.15)',   color: '#00f5ff' },
  change:    { bg: 'rgba(255,196,0,0.15)',   color: '#ffc400' },
  input:     { bg: 'rgba(255,196,0,0.1)',    color: '#cc9d00' },
  mouseenter:{ bg: 'rgba(255,45,120,0.15)',  color: '#ff2d78' },
  mouseleave:{ bg: 'rgba(107,107,138,0.2)',  color: '#6b6b8a' },
  mousemove: { bg: 'rgba(255,45,120,0.08)',  color: '#cc2460' },
  resize:    { bg: 'rgba(255,196,0,0.15)',   color: '#ffc400' },
  scroll:    { bg: 'rgba(255,196,0,0.1)',    color: '#ffc400' },
  copy:      { bg: 'rgba(0,245,255,0.15)',   color: '#00f5ff' },
  cut:       { bg: 'rgba(255,45,120,0.15)',  color: '#ff2d78' },
  paste:     { bg: 'rgba(170,255,0,0.15)',   color: '#aaff00' },
  dragstart: { bg: 'rgba(180,77,255,0.2)',   color: '#b44dff' },
  dragend:   { bg: 'rgba(107,107,138,0.2)',  color: '#6b6b8a' },
  dragover:  { bg: 'rgba(180,77,255,0.1)',   color: '#b44dff' },
  drop:      { bg: 'rgba(170,255,0,0.2)',    color: '#aaff00' },
  DOMContentLoaded: { bg: 'rgba(0,245,255,0.15)', color: '#00f5ff' },
};

function logTo(feedId, eventName, message) {
  const feed = document.getElementById(feedId);
  if (!feed) return;
  const c = tagColors[eventName] || { bg: 'rgba(255,255,255,0.1)', color: '#fff' };
  const entry = document.createElement('div');
  entry.className = 'log-entry';
  entry.innerHTML = `
    <span class="log-tag" style="background:${c.bg};color:${c.color}">${eventName}</span>
    <span class="log-text">${message}</span>
  `;
  feed.prepend(entry);
  // Keep feed trim
  while (feed.children.length > 20) feed.removeChild(feed.lastChild);
}

// ─── UTILITY: TOAST ──────────────────────────────────────────
function showToast(icon, msg, accentColor = 'var(--neon-cyan)') {
  const container = document.getElementById('toast-container');
  const t = document.createElement('div');
  t.className = 'toast';
  t.style.borderLeftColor = accentColor;
  t.innerHTML = `<span class="toast-icon">${icon}</span><span class="toast-msg">${msg}</span>`;
  container.appendChild(t);
  setTimeout(() => {
    t.classList.add('out');
    t.addEventListener('animationend', () => t.remove());
  }, 2800);
}

// ─── CUSTOM CURSOR ────────────────────────────────────────────
const dot  = document.getElementById('cursor-dot');
const ring = document.getElementById('cursor-ring');
let ringX = 0, ringY = 0, dotX = 0, dotY = 0;

document.addEventListener('mousemove', e => {
  dotX  = e.clientX; dotY  = e.clientY;
  dot.style.left  = dotX  + 'px';
  dot.style.top   = dotY  + 'px';
});

function lerpRing() {
  ringX += (dotX - ringX) * 0.12;
  ringY += (dotY - ringY) * 0.12;
  ring.style.left = ringX + 'px';
  ring.style.top  = ringY + 'px';
  requestAnimationFrame(lerpRing);
}
lerpRing();

// Hover detection for cursor morph
document.querySelectorAll('.btn, .input, .drag-item, .mouse-box, .drop-zone').forEach(el => {
  el.addEventListener('mouseenter', () => document.body.classList.add('hovering'));
  el.addEventListener('mouseleave', () => document.body.classList.remove('hovering'));
});

// ─── WINDOW EVENTS ────────────────────────────────────────────
document.addEventListener('DOMContentLoaded', () => {
  logTo('windowLog', 'DOMContentLoaded', 'Page is fully parsed and ready.');
  showToast('⚡', 'DOMContentLoaded fired');
  updateWindowStats();
});

window.addEventListener('resize', () => {
  updateWindowStats(true);
  logTo('windowLog', 'resize', `${window.innerWidth} × ${window.innerHeight}`);
});

window.addEventListener('scroll', () => {
  const sy = Math.round(window.scrollY);
  document.getElementById('scrollY').textContent = sy;
  document.getElementById('statS').classList.add('active');
  clearTimeout(window._scrollTimer);
  window._scrollTimer = setTimeout(() => document.getElementById('statS').classList.remove('active'), 600);
  logTo('windowLog', 'scroll', `scrollY → ${sy}px`);
});

function updateWindowStats(flash = false) {
  document.getElementById('winW').textContent = window.innerWidth;
  document.getElementById('winH').textContent = window.innerHeight;
  document.getElementById('scrollY').textContent = Math.round(window.scrollY);
  if (flash) {
    ['statW','statH'].forEach(id => {
      const el = document.getElementById(id);
      el.classList.add('active');
      setTimeout(() => el.classList.remove('active'), 600);
    });
  }
}

// ─── CLICK EVENT ─────────────────────────────────────────────
const clickBtn   = document.getElementById('clickBtn');
const clickBadge = document.getElementById('clickBadge');
let   clickCount = 0;

clickBtn.addEventListener('click', () => {
  clickCount++;
  clickBtn.classList.remove('fired');
  void clickBtn.offsetWidth; // reflow to restart animation
  clickBtn.classList.add('fired');
  logTo('clickLog', 'click', `Button clicked — total: ${clickCount}`);
  clickBadge.classList.add('visible');
  showToast('🖱️', `Click #${clickCount} registered`);
});

// ─── FOCUS & BLUR ─────────────────────────────────────────────
const focusInput     = document.getElementById('focusInput');
const focusIndicator = document.getElementById('focusIndicator');

focusInput.addEventListener('focus', () => {
  focusIndicator.classList.add('active');
  logTo('focusLog', 'focus', 'Input gained focus');
});
focusInput.addEventListener('blur', () => {
  focusIndicator.classList.remove('active');
  logTo('focusLog', 'blur', 'Input lost focus');
});

// ─── KEYBOARD EVENTS ─────────────────────────────────────────
const keyboardInput = document.getElementById('keyboardInput');
const keyChip       = document.getElementById('keyChip');
let   keyTimer;

keyboardInput.addEventListener('keydown', e => {
  keyChip.textContent = e.key === ' ' ? '⎵' : e.key.length > 1 ? '↵' : e.key;
  keyChip.classList.add('lit');
  clearTimeout(keyTimer);
  keyTimer = setTimeout(() => keyChip.classList.remove('lit'), 300);
  logTo('keyboardLog', 'keydown', `key="${e.key}"  code="${e.code}"`);
});
keyboardInput.addEventListener('keyup', e => {
  logTo('keyboardLog', 'keyup', `key="${e.key}" released`);
});
keyboardInput.addEventListener('keypress', e => {
  logTo('keyboardLog', 'keypress', `character "${e.key}" pressed`);
});

// ─── FORM EVENTS ─────────────────────────────────────────────
const myForm       = document.getElementById('myForm');
const nameInput    = document.getElementById('nameInput');
const typingPreview= document.getElementById('typingPreview');

myForm.addEventListener('submit', e => {
  e.preventDefault();
  const val = nameInput.value.trim();
  logTo('formLog', 'submit', `Submitted: "${val || '(empty)'}"`);
  showToast('✅', `Form submitted: ${val || '(empty)'}`, 'var(--neon-lime)');
  nameInput.value = '';
  typingPreview.textContent = '';
});

nameInput.addEventListener('change', () => {
  logTo('formLog', 'change', `Value changed to: "${nameInput.value}"`);
});

nameInput.addEventListener('input', () => {
  typingPreview.textContent = nameInput.value;
  logTo('formLog', 'input', `Typing: "${nameInput.value}"`);
});

// ─── MOUSE EVENTS ─────────────────────────────────────────────
const mouseBox      = document.getElementById('mouseBox');
const mouseBoxLabel = document.getElementById('mouseBoxLabel');
const mouseBoxCoords= document.getElementById('mouseBoxCoords');
const mouseGlow     = document.getElementById('mouseGlow');

mouseBox.addEventListener('mouseenter', () => {
  mouseBox.classList.add('hovering');
  mouseBoxLabel.textContent = 'You\'re in!';
  logTo('mouseLog', 'mouseenter', 'Cursor entered the zone');
});

mouseBox.addEventListener('mouseleave', () => {
  mouseBox.classList.remove('hovering');
  mouseBoxLabel.textContent = 'Move over me';
  mouseBoxCoords.textContent = 'x: — y: —';
  mouseGlow.style.opacity = '0';
  logTo('mouseLog', 'mouseleave', 'Cursor left the zone');
});

mouseBox.addEventListener('mousemove', e => {
  const rect = mouseBox.getBoundingClientRect();
  const x = Math.round(e.clientX - rect.left);
  const y = Math.round(e.clientY - rect.top);
  mouseBoxCoords.textContent = `x: ${x}  y: ${y}`;
  mouseGlow.style.left = x + 'px';
  mouseGlow.style.top  = y + 'px';
  mouseGlow.style.opacity = '1';
});

mouseBox.addEventListener('click', () => {
  logTo('mouseLog', 'click', 'Mouse clicked inside box');
  showToast('🎯', 'Click inside mouse zone', 'var(--neon-pink)');
});

// ─── CLIPBOARD EVENTS ─────────────────────────────────────────
const clipboardInput = document.getElementById('clipboardInput');
const badgeCopy  = document.getElementById('badgeCopy');
const badgeCut   = document.getElementById('badgeCut');
const badgePaste = document.getElementById('badgePaste');

function flashBadge(badge, cls) {
  badge.classList.add(cls);
  setTimeout(() => badge.classList.remove(cls), 1200);
}

clipboardInput.addEventListener('copy', () => {
  flashBadge(badgeCopy, 'flash-copy');
  logTo('clipLog', 'copy', 'Text copied to clipboard');
  showToast('📋', 'Copied!', 'var(--neon-cyan)');
});
clipboardInput.addEventListener('cut', () => {
  flashBadge(badgeCut, 'flash-cut');
  logTo('clipLog', 'cut', 'Text cut to clipboard');
  showToast('✂️', 'Cut!', 'var(--neon-pink)');
});
clipboardInput.addEventListener('paste', () => {
  flashBadge(badgePaste, 'flash-paste');
  logTo('clipLog', 'paste', 'Text pasted from clipboard');
  showToast('📥', 'Pasted!', 'var(--neon-lime)');
});

// ─── DRAG & DROP ──────────────────────────────────────────────
const dragItem = document.getElementById('dragItem');
const dropZone = document.getElementById('dropZone');

dragItem.addEventListener('dragstart', e => {
  e.dataTransfer.effectAllowed = 'move';
  setTimeout(() => dragItem.classList.add('dragging'), 0);
  logTo('dndLog', 'dragstart', 'Drag initiated');
});

dragItem.addEventListener('dragend', () => {
  dragItem.classList.remove('dragging');
  logTo('dndLog', 'dragend', 'Drag ended');
});

dropZone.addEventListener('dragover', e => {
  e.preventDefault();
  dropZone.classList.add('dragover');
  logTo('dndLog', 'dragover', 'Hovering over drop zone');
});

dropZone.addEventListener('dragleave', () => {
  dropZone.classList.remove('dragover');
});

dropZone.addEventListener('drop', e => {
  e.preventDefault();
  dropZone.classList.remove('dragover');
  dropZone.classList.add('has-item');
  dropZone.innerHTML = '';
  dragItem.classList.remove('dragging');
  dropZone.appendChild(dragItem);
  logTo('dndLog', 'drop', 'Item successfully dropped! 🎉');
  showToast('✦', 'Dropped!', 'var(--neon-violet)');
});
document.querySelectorAll('a').forEach(a => a.addEventListener('click', e => {
   e.preventDefault();
   const href = e.currentTarget.getAttribute('href');
   if (href.startsWith('@')) {
      loadPage(href.slice(1));
   }
}));
$(buttonExit).click(e => {
   loadPage('index');
});

$(buttonCreate).click(async e => {
   const res = await new Promise(res => createGame(res));

   if (res.status == 'OK') {
      loadPage('game');
   } else {
      alert('Ошибка во время создания игры.');
   }
});

$(buttonConnect).click(async e => {
   const sid = prompt('Введите SID игры');
   if (sid == null) return;
   const res = await new Promise(res => connectGame(sid, res));

   if (res.status == 'OK') {
      loadPage('game')
   } else {
      alert('Не удалось подключится к игре. Возможно вы ввели неверный SID');
   }
})
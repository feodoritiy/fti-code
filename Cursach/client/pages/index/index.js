const PROTOCOL = 'http';
const HOST = '127.0.0.1:1234';

const ENTER_DELAY = 900;

buttonRegister.addEventListener('click', async e => {
   const formData = new FormData(form);
   const res = await new Promise(res => register(formData.get('login'), formData.get('password'), res));

   if (res == 'OK') {
      form.classList.add('form_ok');
      setTimeout(() => loadPage('main-menu'), ENTER_DELAY);
   } else { // res == 'Exists'
      alert('Аккаунт с таким логином уже существует, придумайте другой логин.');
   }
});

buttonLogin.addEventListener('click', async e => {
   const formData = new FormData(form);
   const res = await new Promise(res => login(formData.get('login'), formData.get('password'), res));

   if (res == 'OK') {
      form.classList.add('form_ok');
      setTimeout(() => loadPage('main-menu'), ENTER_DELAY);
   } else if (res == 'Wrong-password') {
      alert('Вы ввели неверный пароль.');
   } else { // res == 'Wrong-login'
      alert('Аккаунта с таким логином не существует.');
   }
});
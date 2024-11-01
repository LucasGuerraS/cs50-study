const btnContainer = document.querySelector('.buttons-container');
const btns = btnContainer.querySelectorAll('button');
for (let i = 0; i < btns.length; i++) {
  btns[i].addEventListener('click', () => {
    if (btns[i].innerText == '6') {
      btns[i].style.backgroundColor = 'green';
      document.querySelector('.c1').style.display = 'block';
      document.querySelector('.i1').style.display = 'none';
    } else {
      btns[i].style.backgroundColor = 'red';
      document.querySelector('.c1').style.display = 'none';
      document.querySelector('.i1').style.display = 'block';
    }
  });
}

function checkForm() {
  event.preventDefault();
  let text = document.querySelector('input').value;
  if (text && text.toLowerCase() == 'savathun') {
    document.querySelector('.c2').style.display = 'block';
    document.querySelector('.i2').style.display = 'none';
  } else {
    document.querySelector('.c2').style.display = 'none';
    document.querySelector('.i2').style.display = 'block';
  }
}

document.querySelector('form').addEventListener('submit', checkForm);

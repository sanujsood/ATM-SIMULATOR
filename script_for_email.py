import smtplib
from email.message import EmailMessage
msg = EmailMessage()
msg['Subject'] = 'From my script'
msg['From'] = 'atmproject.sem3@gmail.com'
msg['To'] = 'sanujsood@gmail.com'
smtp = smtplib.SMTP_SSL('smtp.gmail.com', 465)
smtp.login('atmproject.sem3@gmail.com', 'qdtkgrxlncvvzkrd')
msg.set_content('Your OTP for verification of booking is given as :: 12237')
smtp.send_message(msg)
smtp.quit()
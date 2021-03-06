<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<%@ page import="javax.mail.Authenticator" %>
<%@ page import="java.util.Properties" %>
<%@ page import="javax.mail.internet.MimeMessage" %>
<%@ page import="javax.mail.internet.InternetAddress" %>
<%@ page import="javax.mail.Transport" %>
<%@ page import="javax.mail.Session" %>
<%@ page import="javax.mail.PasswordAuthentication" %>
<%@ page import="javax.mail.MessagingException" %>
<%@ page import="javax.mail.Message" %>
<%@ page import="user.STMPAuthenticator" %>
<%@ page import="java.util.Date" %>
<%@ page import="user.AuthenticationNumber" %>
<%!
    String ctxPath = null;
    String email = null;
    AuthenticationNumber an = null;
    String amho = null;
    boolean check = true;
%><%
	ctxPath = request.getContextPath();
	request.setCharacterEncoding("UTF-8");
	
	email = request.getParameter("email");
	if(email == null || email.equals(""))
		System.out.println("email : null");
	else
		System.out.println("email : " + email);
	
	Properties p = new Properties();
	p.put("mail.transport.protocol", "smtp");
	p.put("mail.smtp.host", "smtp.naver.com");
	p.put("mail.smtp.port", "465");
	p.put("mail.smtp.starttls.enable","true");
	p.put("mail.smtp.auth", "true");
	
	an = new AuthenticationNumber();
	amho = an.getNum();
	an.setCode(amho);
	
	try {
		Authenticator auth = new STMPAuthenticator();
		
		Session mailSession = Session.getDefaultInstance(p, auth);
		
		MimeMessage message = new MimeMessage(mailSession);
		InternetAddress from = new InternetAddress("jinjin0816@naver.com");
		message.setFrom(from);
		message.setRecipients(Message.RecipientType.TO, InternetAddress.parse(email));
		message.setSubject("DDaMamIn SNS에서 인증 요청이 왔습니다.");
		message.setContent(an.getHTML(), "text/html; charset=UTF-8");
		message.setSentDate(new Date());
		
		Transport.send(message);
	} catch(MessagingException me) {
		me.printStackTrace();
		//check = false;
	}
	
	if(check) {
		//session.setAttribute("email_value", email);
		Cookie values = new Cookie("email_value", email);
		values.setMaxAge(60*5);
		values.setPath("/");
		response.addCookie(values);
		
		session.setAttribute("amho", amho);
		System.out.println(session.getAttribute("amho"));
		session.setMaxInactiveInterval(60*20);
		
		response.sendRedirect( ctxPath + "/index.jsp" );
		//pageContext.forward( ctxPath + "/index.jsp" );
	}
	else {
		response.sendRedirect( ctxPath + "/checkEmailRes2.jsp");
		//pageContext.forward( ctxPath + "/checkEmailRes2.jsp" );
	}
%>
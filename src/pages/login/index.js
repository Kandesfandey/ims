import React from "react";
import {
  StyledContainer,
  CenteredContainer,
  LeftContainer,
  LoginImage,
  RightContainer,
  RightTitle,
  Input,
  InputTitle,
  FormContainer,
  SubmitButton,
  LogoImage,
  Divider,
  DividerOr,
} from "./styles/login";
import { GoogleLoginButton } from "react-social-login-buttons";
import TeamBaamImage from "../../images/BAAM-logos_transparent.png";
import LoginSVG from "../../images/login.svg";

const Login = () => {
  return (
    <StyledContainer>
      <CenteredContainer>
        <LeftContainer>
          <LoginImage src={LoginSVG} alt="" />
        </LeftContainer>
        <RightContainer>
          <LogoImage src={TeamBaamImage} alt="" />
          <RightTitle>Team Baam's Inventory</RightTitle>
          <FormContainer>
            <InputTitle>Username</InputTitle>
            <Input type="text" />
            <InputTitle>Password</InputTitle>
            <Input type="password" />
            <SubmitButton>Sign In</SubmitButton>
          </FormContainer>
          <Divider>
            <DividerOr>Or</DividerOr>
          </Divider>
          <GoogleLoginButton
            style={{ width: "250px", paddingLeft: "20px", marginLeft: "10px" }}
          />
        </RightContainer>
      </CenteredContainer>
    </StyledContainer>
  );
};

export default Login;

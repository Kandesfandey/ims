import React from 'react'
import SideBar from '../../components/sidebar'
import Navbar from '../../components/navbar'
import { useState } from "react";
import { FormContainer, FormInputContainer, H1Container, DriveFolderUploadOutlinedIcon, ImageContainer, InputContainer, LabelContainer, LeftContainer, NewContainer, NewContainerContainer, RightContainer, TopBottomContainer } from './styles/new';
const New = () => {
    const [file, setFile] = useState("");
  return (
    <NewContainer>
    <SideBar />
    <NewContainerContainer>
      <Navbar />
      <TopBottomContainer>
        <H1Container>{title}</H1Container>
        </TopBottomContainer>
      <TopBottomContainer>
        <LeftContainer>
          <ImageContainer
            src={
              file
                ? URL.createObjectURL(file)
                : "https://icon-library.com/images/no-image-icon/no-image-icon-0.jpg"
            }
            alt=""
          />
        </LeftContainer>
        <RightContainer>
          <FormContainer>
            <FormInputContainer>
              <LabelContainer htmlFor="file">
                Image: <DriveFolderUploadOutlinedIcon />
              </LabelContainer>
              <InputContainer
                type="file"
                id="file"
                onChange={(e) => setFile(e.target.files[0])}
                style={{ display: "none" }}
              />
            </FormInputContainer>

            {inputs.map((input) => (
              <FormInputContainer key={input.id}>
                <LabelContainer>{input.label}</LabelContainer>
                <InputContainer type={input.type} placeholder={input.placeholder} />
              </FormInputContainer>
            ))}
            <button>Send</button>
            </FormContainer>
          </RightContainer>
        </TopBottomContainer>
      </NewContainerContainer>
    </NewContainer>
  )
}

export default New
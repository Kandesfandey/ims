import React from 'react'
import SideBar from '../../components/sidebar'
import Navbar from '../../components/navbar'
import { BottomContainer, DetailItemContainer, DetailsContainer, EditButtonContainer, ItemContainer, ItemImageContainer, ItemKeyContainer, ItemTitleContainer, ItemValueContainer, LeftContainer, RightContainer, SingleUserContainer, TitleContainer, TopContainer, UserContainer } from './styles/user'
const User = () => {
  return (
    <UserContainer>
    <SideBar />
    <SingleUserContainer>
      <Navbar />
      <TopContainer>
        <LeftContainer>
          <EditButtonContainer>Edit</EditButtonContainer>
          <TitleContainer>Information</TitleContainer>
          <ItemContainer>
            <ItemImageContainer
              src="https://images.pexels.com/photos/733872/pexels-photo-733872.jpeg?auto=compress&cs=tinysrgb&dpr=3&h=750&w=1260"
              alt=""
            />
            <DetailsContainer>
              <ItemTitleContainer>Jane Doe</ItemTitleContainer>
              <DetailItemContainer>
                <ItemKeyContainer>Email:</ItemKeyContainer>
                <ItemValueContainer>janedoe@gmail.com</ItemValueContainer>
                </DetailItemContainer>
              <DetailItemContainer>
                <ItemKeyContainer>Phone:</ItemKeyContainer>
                <ItemValueContainer>+1 2345 67 89</ItemValueContainer>
                </DetailItemContainer>
              <DetailItemContainer>
                <ItemKeyContainer>Address:</ItemKeyContainer>
                <ItemValueContainer>
                  Elton St. 234 Garden Yd. NewYork
                  </ItemValueContainer>
                </DetailItemContainer>
              <DetailItemContainer>
                <ItemKeyContainer>Country:</ItemKeyContainer>
                <ItemValueContainer>USA</ItemValueContainer>
                </DetailItemContainer>
              </DetailsContainer>
            </ItemContainer>
          </LeftContainer>
        <RightContainer>
        </RightContainer>
        </TopContainer>
      <BottomContainer>
      <TitleContainer>Last Transactions</TitleContainer>
        </BottomContainer>
    </SingleUserContainer>
    </UserContainer>
  )
}

export default User
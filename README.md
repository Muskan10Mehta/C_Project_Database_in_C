# SupportTicket Management system for hackathons with lightweight Database in C 

# Project description:
<p>This project is for implementing a compact database which will be light weight and fast. This will provide essential features of database management like - create,  update ,search, delete, display. Such databases can be accomodated in devices with very low and constrained amount of resources like embedded systems, small scale projects etc. no need to set up large databases for just a few tables. </p>
<p> <h3> What is a Support Ticket Management System?</h3>
  <p> A Support Ticket management system used in hackathons is a simple smooth way to handle complaints and provide support like mentorship. 
    Anyone can generate a ticket with the issue they are facing, in which field and their team number. The concerned officials like student mentors or organizers can view the tickets and work on the issue and later mark them resolved. 
  </p>
</p>
  
# Goals:
  <p>
  <ol>
  <li>Make a fast and efficient structure for quick operations. </li>
  <li>Add all essential features of a database management system.  </li>
  <li>Make a user friendly design. </li></ol>
  </p>
  
# Specifications:
  <p>This program can perform basic CRUD (create, read, update, delete) operations. The aim is to make it efficient and easy to use.</p>
  
# Design:
  <p>
  <ol>
  <li> Two Structs for defining the table sturctures: 
    <ul>
      <li> Ticket Table: stores the information of all the tickets generated, it stores following information for each ticket
        <ol>
          <li> Team Number </li>
            <li> Team Code </li>
             <li> Stack used in project </li>
               <li> Timestamp for time the ticket is generated </li>
                <li> Pointer to next ticket </li>
        </ol>
      </li>
      <li> Resolved Ticket Table: stores the information of all the resolved tickets 
                <ol>
          <li> Team Number </li>
            <li> Team Code </li>
             <li> Stack used in project </li>
               <li> Timestamp for time the ticket is generated </li>
                  <li> Timestamp for time the ticket is resolved </li>
                <li> Pointer to next ticket </li>
        </ol>
      </li>
    </ul>
    </li>
  <li> Choices for functions help text to perform functions on the database, printing on loop after every command executed.</li>
    <li> Functions: <ul>
      <li><b>Generate issue ticket</b>: Generates a new ticket and adds it to Ticket table</li>
      <li><b>Display all tickets </b>: Prints all tickets from the Ticket table</li>
      <li><b>Modify tickets </b>: Update exisiting ticket information</li>
      <li><b>Delete ticket </b>: Delete a ticket</li>
      <li><b>Search ticket </b>: Search for a ticket by ticket number, team code or stack code </li>
      <li><b>Resolve issue </b>: Mark a ticket as resolved</li>
      <li><b>Display resolved tickets </b>: Prints all the resolved tickets from the Resolved Tickets table</li>
      </ul>
    </li>
  </ol>
  </p>
  

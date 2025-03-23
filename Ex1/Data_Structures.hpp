#pragma once

namespace graph {

    // הצהרה על מחלקת DynamicArray לניהול מערך דינמי של מספרים שלמים
    class DynamicArray {
    private:
        int* arr;         // המערך עצמו
        int size;         // גודל נוכחי של המערך (מספר האיברים)
        int capacity;     // קיבולת המערך (גודל המערך שהוקצה)

    public:
        // בנאי
        DynamicArray();
        
        // בנאי העתקה
        DynamicArray(const DynamicArray& other);
        
        // הרס
        ~DynamicArray();
        
        // אופרטור השמה
        DynamicArray& operator=(const DynamicArray& other);
        
        // הוספת איבר בסוף המערך
        void push_back(int value);
        
        // הסרת האיבר האחרון
        void pop_back();
        
        // גישה לאיבר במיקום מסוים (לקריאה בלבד)
        int at(int index) const;
        
        // גישה לאיבר במיקום מסוים (לקריאה וכתיבה)
        int& at(int index);
        
        // החזרת גודל המערך
        int getSize() const;
        
        // בדיקה האם המערך ריק
        bool isEmpty() const;
        
        // ניקוי המערך
        void clear();
        
        // בדיקה האם ערך קיים במערך
        bool contains(int value) const;
        
        // הסרת איבר לפי ערך (מוצא את הראשון ומסיר אותו)
        bool remove(int value);
    };

    // הצהרה על מחלקת Queue - תור בסיסי לאלגוריתמים כמו BFS
    class Queue {
    private:
        int* arr;         // המערך שמייצג את התור
        int capacity;     // קיבולת התור
        int front;        // האינדקס של האיבר הראשון בתור
        int rear;         // האינדקס של המקום הפנוי הבא בתור
        int size;         // מספר האיברים בתור

    public:
        // בנאי - מקבל את הגודל המקסימלי של התור
        Queue(int capacity);
        
        // הרס
        ~Queue();
        
        // הוספת איבר לסוף התור
        void enqueue(int value);
        
        // הוצאת האיבר הראשון מהתור
        int dequeue();
        
        // הצצה באיבר הראשון בתור מבלי להסיר אותו
        int peek() const;
        
        // בדיקה האם התור ריק
        bool isEmpty() const;
        
        // בדיקה האם התור מלא
        bool isFull() const;
        
        // החזרת מספר האיברים בתור
        int getSize() const;
    };

}  // namespace graph
/*
 *  This file is part of MUSIC.
 *  Copyright (C) 2008, 2009 INCF
 *
 *  MUSIC is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MUSIC is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MUSIC_SYNCHRONIZER_HH

#include <music/clock.hh>

namespace MUSIC {

  class Synchronizer {
  protected:
    Clock* localTime;
    Clock nextSend;
    Clock nextReceive;
    ClockState latency_;
    int maxBuffered_;
    bool interpolate_;
    bool communicate_;
    void nextCommunication ();
    void setMaxDelay (ClockState maxDelay, Clock& clock);
  public:
    void setLocalTime (Clock* lt);
    virtual void setSenderTickInterval (ClockState ti);
    virtual void setReceiverTickInterval (ClockState ti);
    // algorithm expects *extra* buffered ticks so we subtract 1
    void setMaxBuffered (int m);
    int allowedBuffered () { return maxBuffered_; }
    void setAccLatency (ClockState l);
    ClockState delay () { return latency_; }
    void setInterpolate (bool flag);
    void setMaxDelay (ClockState maxDelay);
    virtual void initialize ();
    bool communicate ();
    bool simulating ();
  };


  class OutputSynchronizer : virtual public Synchronizer {
  public:
    void tick ();
  };


  class InputSynchronizer : virtual public Synchronizer {
  public:
    void tick ();
  };


  class InterpolationSynchronizer : virtual public Synchronizer {
  protected:
    Clock remoteTime;
  public:
    virtual void setSenderTickInterval (ClockState ti);
    virtual void setReceiverTickInterval (ClockState ti);    
    void remoteTick ();
  };


  class InterpolationOutputSynchronizer : public InterpolationSynchronizer,
					  public OutputSynchronizer {
  public:
    void initialize ();
    bool sample ();
    bool interpolate ();
    double interpolationCoefficient ();
    void tick ();
  };


  class InterpolationInputSynchronizer : public InterpolationSynchronizer,
					 public InputSynchronizer {
  public:
    void initialize ();
    bool sample ();
    double interpolationCoefficient ();
    void tick ();
  };

}

#define MUSIC_SYNCHRONIZER_HH
#endif
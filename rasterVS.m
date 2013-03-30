function [oQ oQcol] = rasterVS(Q, Qcol, ModelViewProj, P, d, h, mirror_norm)
    
    % define ray from reflected projector position P? to vertex Q    
    PQ = Q-P;
    PQ = PQ/norm(PQ);
    
    % compute intersection of ray PQ with vertical cylinder with
    % radius d to find view position V?
    V = intersectLineCylinder(cat(2,[0 0 0], PQ), [0 0 0 0 0 0 d], 'checkBounds', FALSE);
    V = [V(1) h V(2)]; % set correct viewer height
    
    % define ray from ideal viewing position V? to vertex Q
    VQ = Q-V;
    VQ = VQ/norm(VQ);
    
    % compute intersection ray VQ with mirror plane to find point M
    M = intersectLinePlane(cat(2,[0 0 0], VQ), mirror_norm);
    
    oQ = projPointOnPlane(M, ModelViewProj); % project M into projector
    oQcol = Qcol; % keep the existing vertex color
    
    % recompute depth in based on distance from V?
    z = distancePoints3d(V, Q) / 2* distancePoints3d(V, M);
    oQ = [oQ(1) oQ(2) z];
end
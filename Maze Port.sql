
/*
Portal Master Option
By Rochet2
Downloaded from http://projectcode.zzl.org/
Bugs and contact with E-mail: Rochet2@post.com
*/

SET
@BIG := (SELECT id FROM gossip_menu_option WHERE menu_id='50000' ORDER BY id DESC LIMIT 1),
@SMALL := (SELECT id FROM gossip_menu_option WHERE menu_id='50000' ORDER BY id ASC LIMIT 1),
@START := 1 + 1;

UPDATE gossip_menu_option
SET id = @BIG + id + @START
WHERE menu_id='50000';

UPDATE gossip_menu_option
SET id = id - @BIG - 1
WHERE menu_id='50000';

UPDATE conditions
SET SourceEntry = @BIG + SourceEntry + @START
WHERE SourceTypeOrReferenceId = 15 and SourceGroup = '50000';

UPDATE conditions
SET SourceEntry = SourceEntry - @BIG - 1
WHERE SourceTypeOrReferenceId = 15 and SourceGroup = '50000';

UPDATE smart_scripts
SET event_param2 = @BIG + event_param2 + @START
WHERE entryorguid='1900001' AND event_param1 = '50000';

UPDATE smart_scripts
SET event_param2 = event_param2 - @BIG - 1
WHERE entryorguid='1900001' AND event_param1 = '50000';


INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, box_money, box_text) VALUES
('50000', @SMALL, '0', 'Maze Port', 1, 1, '50000', '0', 'Are you sure?');

SET @SID := (SELECT id FROM smart_scripts WHERE entryorguid = '1900001' ORDER BY id DESC LIMIT 1)+1;
INSERT INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES 
('1900001', 0, IFNULL(@SID, 1), 0, 62, 0, 100, 0, '50000', @SMALL, 0, 0, 62, '0', 0, 0, 0, 0, 0, 0, 8, 0, 0, '-7398.118164', '795.607544', '131.408005', '0', 'Teleporter script - Custom');

/*
Portal Master Option
By Rochet2
Downloaded from http://projectcode.zzl.org/
Bugs and contact with E-mail: Rochet2@post.com
*/

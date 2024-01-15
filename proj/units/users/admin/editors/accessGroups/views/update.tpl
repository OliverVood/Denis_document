<?php

	namespace Proj\Templates\Editor\AccessGroups;

	use Base\Access;
	use Base\Editor\Editor;
	use Base\Editor\Skins\Edit\Hidden;
	use Base\Templates\Buffering;
	use Proj\Units\Consts;

	abstract class Update {

		public static function ToVar(Editor $editor, int $gid, array $collections, array $items, string $title, array $navigate): string {
			Buffering::Start();
			self::Render($editor, $gid, $collections, $items, $title, $navigate);
			return Buffering::Read();
		}

		public static function Render(Editor $editor, int $gid, array $collections, array $items, string $title, array $navigate): void { ?>
			<div class = "navigate">
				<?php foreach ($navigate as $func) echo $func(); ?>
			</div>
			<h1><?= $title; ?></h1>
			<form action = "<?= $editor->do_update->GetPath(); ?>" class = "cn-mb-1">
				<?php
					(new Hidden('gid', 'gid'))->Render($gid);
				foreach ($collections as $collectionID => $collection) {
					if (!Access::Allow(\Base\Editor\Access::ACCESS_SETTING, $collectionID)) continue;
				?>
					<h3 class = "cn-mb-1"><?= $collection['title']; ?></h3>
					<table class = "select cn-mb-1">
						<thead>
							<tr>
								<th>Право</th>
								<th>Не выбрано</th>
								<th>Разрешено</th>
								<th>Запрещено</th>
							</tr>
						</thead>
							<tbody>
							<?php foreach ($collection['rights'] as $right) { ?>
								<tr>
									<td><?= $right['title']; ?></td>
									<td class = "cn-center"><input type = "radio" name = "rights[<?= $collectionID; ?>][<?= $right['id']; ?>]" value = "<?= Consts\Users::PERMISSION_UNDEFINED; ?>"<?= (isset($items[$collectionID][$right['id']]) && ($items[$collectionID][$right['id']] == Consts\Users::PERMISSION_UNDEFINED)) ? ' checked': ''; ?>></td>
									<td class = "cn-center"><input type = "radio" name = "rights[<?= $collectionID; ?>][<?= $right['id']; ?>]" value = "<?= Consts\Users::PERMISSION_YES; ?>"<?= (isset($items[$collectionID][$right['id']]) && ($items[$collectionID][$right['id']] == Consts\Users::PERMISSION_YES)) ? ' checked': ''; ?>></td>
									<td class = "cn-center"><input type = "radio" name = "rights[<?= $collectionID; ?>][<?= $right['id']; ?>]" value = "<?= Consts\Users::PERMISSION_NO; ?>"<?= (isset($items[$collectionID][$right['id']]) && ($items[$collectionID][$right['id']] == Consts\Users::PERMISSION_NO)) ? ' checked': ''; ?>></td>
								</tr>
							<?php } ?>
						</tbody>
					</table>
				<?php } ?>
				<input type = "submit" value = "Изменить" onclick = "<?= $editor->do_update->GetClick(); ?>">
			</form>
		<?php }

	}
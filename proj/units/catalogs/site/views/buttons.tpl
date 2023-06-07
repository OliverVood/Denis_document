<?php

	namespace Proj\Site\Templates\Catalogs;

	use Base\Templates\Buffering;
	use Proj\Site\Actions;

	abstract class Buttons {

		public static function ToVar(): string {
			Buffering::Start();
			self::Render();
			return Buffering::Read();
		}

		public static function Render(): void { ?>
			<div class = "view catalogs buttons">
				<div class = "grid col_1">
					<div>
						<h1>Начните работу прямо сейчас</h1>
					</div>
				</div>
				<div class = "btns">
					<?= Actions\Catalogs::$action_estimate->GetLinkHref('Сметы »', [], ['class' => 'button']); ?>
					<?= Actions\Catalogs::$action_certificate->GetLinkHref('Акты выполненных работ »', [], ['class' => 'button']); ?>
					<?= Actions\Catalogs::$action_price_list->GetLinkHref('Прайс-листы »', [], ['class' => 'button']); ?>
				</div>
			</div>
		<?php }

	}